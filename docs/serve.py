#!/usr/bin/env python3
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
from urllib.parse import parse_qs, unquote, urlparse
import argparse
import json
import re
import subprocess
import sys
import webbrowser


ROOT = Path(__file__).resolve().parent


def safe_path(raw):
    raw = unquote(raw).lstrip("/")
    path = (ROOT / raw).resolve()
    if path != ROOT and ROOT not in path.parents:
        return None
    return path


def read_title(path):
    try:
        text = path.read_text(encoding="utf-8")
    except UnicodeDecodeError:
        return path.stem

    if text.startswith("---"):
        end = text.find("\n---", 3)
        if end != -1:
            front = text[3:end]
            for line in front.splitlines():
                key, sep, value = line.partition(":")
                if sep and key.strip() == "title":
                    return value.strip().strip("\"'")

    match = re.search(r"^#\s+(.+)$", text, re.MULTILINE)
    if match:
        return match.group(1).strip()
    return path.stem


def docs_index():
    files = []
    for path in sorted(ROOT.rglob("*.md")):
        relative = path.relative_to(ROOT)
        if any(part.startswith(".") for part in relative.parts):
            continue
        rel = relative.as_posix()
        files.append({
            "path": rel,
            "title": read_title(path),
            "group": rel.split("/", 1)[0] if "/" in rel else "root",
        })
    files.sort(key=lambda x: (x["path"] != "README.md", x["path"]))
    return files


class DocsHandler(SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=str(ROOT), **kwargs)

    def log_message(self, fmt, *args):
        sys.stderr.write("%s - %s\n" % (self.address_string(), fmt % args))

    def send_json(self, data):
        body = json.dumps(data, ensure_ascii=False).encode("utf-8")
        self.send_response(200)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def send_text(self, text, content_type="text/plain; charset=utf-8"):
        body = text.encode("utf-8")
        self.send_response(200)
        self.send_header("Content-Type", content_type)
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def send_error_text(self, status, text):
        body = text.encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "text/plain; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def do_GET(self):
        parsed = urlparse(self.path)

        if parsed.path in ("", "/"):
            self.path = "/viewer.html"
            return super().do_GET()

        if parsed.path == "/api/files":
            return self.send_json(docs_index())

        if parsed.path == "/api/doc":
            query = parse_qs(parsed.query)
            raw = query.get("path", ["README.md"])[0]
            path = safe_path(raw)
            if path is None or path.suffix != ".md" or not path.is_file():
                return self.send_error_text(404, "Markdown file not found")
            return self.send_text(path.read_text(encoding="utf-8"), "text/markdown; charset=utf-8")

        return super().do_GET()

    def do_HEAD(self):
        parsed = urlparse(self.path)
        if parsed.path in ("", "/"):
            self.path = "/viewer.html"
        return super().do_HEAD()


def make_server(host, port):
    last_error = None
    for candidate in range(port, port + 50):
        try:
            return ThreadingHTTPServer((host, candidate), DocsHandler)
        except OSError as error:
            last_error = error
    raise last_error


def open_chrome(url):
    if sys.platform == "darwin":
        try:
            subprocess.Popen(["open", "-a", "Google Chrome", url])
            return
        except OSError:
            pass
    webbrowser.open(url)


def main():
    parser = argparse.ArgumentParser(description="Serve library Markdown docs.")
    parser.add_argument("--host", default="127.0.0.1")
    parser.add_argument("--port", type=int, default=8000)
    parser.add_argument("--no-open", action="store_true")
    args = parser.parse_args()

    server = make_server(args.host, args.port)
    host, port = server.server_address
    url = f"http://{host}:{port}/"
    print(f"Serving {ROOT}")
    print(f"Open {url}")
    if not args.no_open:
        open_chrome(url)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\nStopped")


if __name__ == "__main__":
    main()
