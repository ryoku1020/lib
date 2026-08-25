#pragma once
#ifndef EPS
#define EPS 0
#endif
template<class T>
int sign(T x);

template<class T>
ld ArcTan(T x,T y){
    if(x==0&&y==0)return 0;
    return atan2l((ld)y,(ld)x);
}
i128 abs(i128 x){
    return x<0?-x:x;
}
template<class Point_type,Point_type eps=EPS>
struct Point{
    using Ptype=Point_type;
    Point_type x,y;
    Point&operator+=(const Point&p){
        x+=p.x,y+=p.y;
        return *this;
    }
    Point&operator-=(const Point&p){
        x-=p.x,y-=p.y;
        return *this;
    }
    Point&operator*=(const Point&p){
        return *this=Point(x*p.x-y*p.y,x*p.y+y*p.x);
    }
    Point&operator*=(const Point_type&v){
        return *this=Point(x*v,y*v);
    }
    Point&operator/=(const Point_type&v){
        return *this=Point(x/v,y/v);
    }
    Point operator-(){
        return Point(-x,-y);
    }
    friend Point operator+(Point p1,const Point&p2){
        return Point(p1)+=p2;
    }
    friend Point operator-(Point p1,const Point&p2){
        return Point(p1)-=p2;
    }
    friend Point operator*(Point p1,const Point&p2){
        return Point(p1)*=p2;
    }
    friend Point operator*(Point p1,const Point_type&p2){
        return Point(p1)*=p2;
    }
    friend Point operator*(const Point_type&p1,Point p2){
        return Point(p2)*=p1;
    }
    friend Point operator/(Point p1,const Point_type&p2){
        return Point(p1)/=p2;
    }
    //res=0:90 res>0:鋭角 res<0:鈍角
    Point_type Dot(const Point&b)const{
        return x*b.x+y*b.y;
    }
    //res=0:平行 res>0:b が a からみて反時計回りの位置 res<0:逆
    Point_type Cross(const Point&b)const{
        return x*b.y-y*b.x;
    }
    ld abs()const{
        return sqrtl((ld)x*x+(ld)y*y);
    }
    //y=0 とかに注意
    ld arg()const{
        return atan2(y,x);
    }
    bool operator==(const Point&p) const{
        return std::abs(p.x-x)<=eps&&std::abs(p.y-y)<=eps;
    }
    bool operator!=(const Point&p) const{
        return !(*this==p);
    }
    int operator<=>(const Point&p) const{
        if(*this==p)return 0;
        auto side=[&](Point a){
            int sx=sign(a.x),sy=sign(a.y);
            if(sx==0&&sy==0)return 1;
            if(sy<0)return 0;
            if(sy==0&&sx>=0)return 1;
            if(sy>0)return 2;
            return 3;
        };
        Point a=*this,b=p;
        int sa=side(a),sb=side(b);
        if(sa!=sb)return sa<sb?-1:1;
        auto cr=a.Cross(b);
        int sc=sign(cr);
        if(sc!=0)return sc>0?-1:1;
        int sx=sign(x-p.x);
        if(sx!=0)return sx<0?-1:1;
        int sy=sign(y-p.y);
        if(sy!=0)return sy<0?-1:1;
        return 0;
    }
    friend istream&operator>>(istream&is,Point&f){
        is>>f.x>>f.y;
        return is;
    }
    #ifdef LOCAL
    friend ostream&operator<<(ostream&os,const Point&f){
        os<<"("<<f.x<<","<<f.y<<")";
        return os;
    }
    #endif
};

template<class Point>
struct Line{
    Point a,b;
    int operator<=>(const Line&p) const{
        if(auto c=a<=>p.a;c!=0)return c;
        return b<=>p.b;
    }
    typename Point::Ptype Y(typename Point::Ptype x) const{
        static_assert(!is_integral_v<typename Point::Ptype>);
        assert(sign(b.x-a.x)!=0);
        return a.y+(b.y-a.y)*(x-a.x)/(b.x-a.x);
    }
    void normalize(){
        Point from=a,v=b-a;
        v/=v.abs();
        if(sign(v.x)<0||(sign(v.x)==0&&sign(v.y)<0))v*=-1;
        from=Projection(Line{from,from+v},{0,0});
        a=from,b=from+v;
    }
};

template<class Point>
struct Segment{
    Point a,b;
    int operator<=>(const Segment&p) const{
        if(auto c=a<=>p.a;c!=0)return c;
        return b<=>p.b;
    }
};

template<class Point>
struct Circle{
    Point c;
    ld r;
    int operator<=>(const Circle&p) const{
        if(auto res=c<=>p.c;res!=0)return res;
        if(r!=p.r)return r<p.r?-1:1;
        return 0;
    }
    bool Contain(Point a)const{
        return (c-a).Dot(c-a)<=r*r+EPS;
    }
};

template<class Point>
Line<Point>line(Point a,Point b){
    return {a,b};
}

template<class Point>
Segment<Point>segment(Point a,Point b){
    return {a,b};
}

template<class Point>
Circle<Point>circle(Point c,ld r){
    return {c,r};
}

template<class T>
int sign(T x){
    if(x>EPS)return 1;
    if(x<-EPS)return -1;
    return 0;
}

//a->b->c 
//a->b b->c で左に曲がる: 1
//a->b b->c で右に曲がる: -1
//c-a-b の order: -2
//a-b-c の order: 2
//a-c-b の order: 0
template<class Point>
int iSP(Point a,Point b,Point c){
    auto cr=(b-a).Cross(c-a);
    if(sign(cr)>0)return 1;
    if(sign(cr)<0)return -1;
    if(sign((b-a).Dot(c-a))<0)return -2;
    if(sign((a-b).Dot(c-b))<0)return 2;
    return 0;
}

template<class Point>
bool LPInter(Line<Point>l,Point p){
    return sign((l.b-l.a).Cross(p-l.a))==0;
}

template<class Point>
bool SPInter(Segment<Point>s,Point p){
    return iSP(s.a,s.b,p)==0;
}

template<class Point>
bool OnLine(Line<Point>l,Point p){
    return LPInter(l,p);
}

template<class Point>
bool OnSegment(Segment<Point>s,Point p){
    return SPInter(s,p);
}

//整数形で扱ってほしい
template<class Point>
vc<Point>convex_hull(vc<Point>points,bool containboundary=false){
    sort(all(points),[&](auto a,auto b){
        if(a.x!=b.x)return a.x<b.x;
        return a.y<b.y;
    });
    points.erase(unique(all(points)),points.end());
    if(points.size()<=2)return points;
    auto bad=[&](auto x){
        if(containboundary)return x<-EPS;
        else return x<=EPS;
    };
    vc<Point>lower_convexhull{points[0],points[1]},upper_convexhull{points[points.size()-1],points[points.size()-2]};
    REP(i,2,points.size()){
        while(lower_convexhull.size()>=2){
            auto pb1=lower_convexhull.back();lower_convexhull.pop_back();
            auto pb2=lower_convexhull.back();
            if(bad((pb1-pb2).Cross(points[i]-pb1))){
                continue;
            }
            lower_convexhull.push_back(pb1);break;
        }
        lower_convexhull.push_back(points[i]);
    }
    DREP(i,(int)points.size()-3,0){
        while(upper_convexhull.size()>=2){
            auto pb1=upper_convexhull.back();upper_convexhull.pop_back();
            auto pb2=upper_convexhull.back();
            if(bad((pb1-pb2).Cross(points[i]-pb1))){
                continue;
            }
            upper_convexhull.push_back(pb1);break;
        }
        upper_convexhull.push_back(points[i]);
    }
    REP(i,1,upper_convexhull.size()-1){
        lower_convexhull.push_back(upper_convexhull[i]);
    }
    if(containboundary){
        lower_convexhull.erase(unique(all(lower_convexhull)),lower_convexhull.end());
    }
    pair<Point,int>idx{lower_convexhull[0],0};
    rep(i,lower_convexhull.size()){
        if(idx.first.y>lower_convexhull[i].y||(idx.first.y==lower_convexhull[i].y&&idx.first.x>lower_convexhull[i].x)){
            idx={lower_convexhull[i],i};
        }
    }
    rotate(lower_convexhull.begin(),lower_convexhull.begin()+idx.second,lower_convexhull.end());
    return lower_convexhull;
}

template<class Point>
vc<pair<Point,int>>convex_hull(vc<pair<Point,int>>points,bool containboundary=false){
    sort(all(points),[&](auto a,auto b){
        if(a.first.x!=b.first.x)return a.first.x<b.first.x;
        if(a.first.y!=b.first.y)return a.first.y<b.first.y;
        return a.second<b.second;
    });
    points.erase(unique(all(points),[&](auto a,auto b){
        return a.first==b.first;
    }),points.end());
    if(points.size()<=2)return points;
    auto bad=[&](auto x){
        if(containboundary)return x<-EPS;
        else return x<=EPS;
    };
    vc<pair<Point,int>>lower_convexhull{points[0],points[1]},upper_convexhull{points[points.size()-1],points[points.size()-2]};
    REP(i,2,points.size()){
        while(lower_convexhull.size()>=2){
            auto pb1=lower_convexhull.back();lower_convexhull.pop_back();
            auto pb2=lower_convexhull.back();
            if(bad((pb1.first-pb2.first).Cross(points[i].first-pb1.first))){
                continue;
            }
            lower_convexhull.push_back(pb1);break;
        }
        lower_convexhull.push_back(points[i]);
    }
    DREP(i,(int)points.size()-3,0){
        while(upper_convexhull.size()>=2){
            auto pb1=upper_convexhull.back();upper_convexhull.pop_back();
            auto pb2=upper_convexhull.back();
            if(bad((pb1.first-pb2.first).Cross(points[i].first-pb1.first))){
                continue;
            }
            upper_convexhull.push_back(pb1);break;
        }
        upper_convexhull.push_back(points[i]);
    }
    REP(i,1,upper_convexhull.size()-1){
        lower_convexhull.push_back(upper_convexhull[i]);
    }
    if(containboundary){
        lower_convexhull.erase(unique(all(lower_convexhull),[&](auto a,auto b){
            return a.first==b.first;
        }),lower_convexhull.end());
    }
    pair<Point,int>idx{lower_convexhull[0].first,0};
    rep(i,lower_convexhull.size()){
        if(idx.first.y>lower_convexhull[i].first.y||(idx.first.y==lower_convexhull[i].first.y&&idx.first.x>lower_convexhull[i].first.x)){
            idx={lower_convexhull[i].first,i};
        }
    }
    rotate(lower_convexhull.begin(),lower_convexhull.begin()+idx.second,lower_convexhull.end());
    return lower_convexhull;
}

template<class Point>
vc<pair<Point,int>>ConvexHullIndex(vc<Point>points,bool containboundary=false){
    vc<pair<Point,int>>P(points.size());
    rep(i,points.size())P[i]={points[i],i};
    return convex_hull(P,containboundary);
}
 
template<class Point>
//線分s と線分t が交わるか(端点も含む）
bool SSInter(Segment<Point>s,Segment<Point>t){
    return iSP(s.a,s.b,t.a)*iSP(s.a,s.b,t.b)<=0&&iSP(t.a,t.b,s.a)*iSP(t.a,t.b,s.b)<=0;
}

template<class Point>
//0:なし
//1:一点のみ
//2:無限個
pair<int,Point>LLInter(Line<Point>l,Line<Point>m){
    static_assert(!is_integral_v<typename Point::Ptype>);
    if(sign((l.b-l.a).Cross(m.a-m.b))!=0){
        using P=typename Point::Ptype;
        P s1=(m.b-m.a).Cross(m.a-l.a);
        P s2=(m.b-m.a).Cross(l.b-l.a);
        P rate=s1/s2;
        return {1,l.a*(1-rate)+l.b*rate};
    }
    if(sign((l.b-l.a).Cross(m.a-l.a))!=0){
        return {0,{}};
    }
    return {2,{}};
}
template<class Point>
//0:なし
//1:一点のみ
//2:無限個
pair<int,Point>LSInter(Line<Point>l,Segment<Point>s){
    auto res=LLInter(l,line(s.a,s.b));
    if(res.first!=1)return res;
    if(SPInter(s,res.second)){
        return res;
    }else{
        return {0,{}};
    }
}
template<class Point>
pair<int,Point>SLInter(Segment<Point>s,Line<Point>l){
    return LSInter(l,s);
}
template<class Point>
ld LPdist(Line<Point>l,Point p){
    static_assert(!is_integral_v<typename Point::Ptype>);
    return abs((l.b-l.a).Cross(p-l.a)/(l.b-l.a).abs());
}
template<class Point>
ld SPdist(Segment<Point>s,Point p){
    if((s.b-s.a).Dot(p-s.a)<-EPS||(s.a-s.b).Dot(p-s.b)<-EPS){
        return min((s.a-p).abs(),(s.b-p).abs());
    }else{
        return LPdist(line(s.a,s.b),p);
    }
}
template<class Point>
ld LLdist(Line<Point>l,Line<Point>m){
    if(LLInter(l,m).first==0){
        return LPdist(l,m.a);
    }
    return 0;
}
template<class Point>
ld LSdist(Line<Point>l,Segment<Point>s){
    auto [type,p]=LLInter(l,line(s.a,s.b));
    int does=(type==2||(type==1&&SPInter(s,p)));
    if(does){
        return 0;
    }
    return min(LPdist(l,s.a),LPdist(l,s.b));
}
template<class Point>
ld SLdist(Segment<Point>s,Line<Point>l){
    return LSdist(l,s);
}
template<class Point>
ld SSdist(Segment<Point>s,Segment<Point>t){
    if(SSInter(s,t))return 0;
    return min({SPdist(s,t.b),SPdist(s,t.a),SPdist(t,s.a),SPdist(t,s.b)});
}
template<class Point>
int SCInter(Segment<Point>s,Circle<Point>c){
    return SPdist(s,c.c)<=c.r+EPS&&max((s.a-c.c).abs(),(s.b-c.c).abs())+EPS>=c.r;
}
template<class Point>
int SCInter(Circle<Point>c,Segment<Point>s){
    return SCInter(s,c);
}
template<class Point>
int CSInter(Circle<Point>c,Segment<Point>s){
    return SCInter(s,c);
}
template<class Point>
tuple<int,Point,Point>LCInter(Line<Point>l,Circle<Point>c){
    static_assert(!is_integral_v<typename Point::Ptype>);
    Point h=Projection(l,c.c);
    ld d=(h-c.c).abs();
    if(d-c.r>EPS)return {0,{},{}};
    if(sign(d-c.r)==0)return {1,h,h};
    Point v=l.b-l.a;
    ld w=sqrtl(max<ld>(c.r*c.r-d*d,0.0l));
    v*=w/v.abs();
    return {2,h+v,h-v};
}
template<class Point>
tuple<int,Point,Point>LCInter(Circle<Point>c,Line<Point>l){
    return LCInter(l,c);
}
template<class Point>
tuple<int,Point,Point>CLInter(Circle<Point>c,Line<Point>l){
    return LCInter(l,c);
}
template<class Point>
tuple<int,Point,Point>CCInter(Circle<Point>c1,Circle<Point>c2){
    static_assert(!is_integral_v<typename Point::Ptype>);
    ld d=(c1.c-c2.c).abs();
    if(sign(d)==0){
        if(sign(c1.r-c2.r)==0)return {-1,{},{}};
        return {0,{},{}};
    }
    int dif=sign(d-abs(c1.r-c2.r));
    int sum=sign(d-c1.r-c2.r);
    if(dif<0)return {0,{},{}};
    if(sum>0)return {4,{},{}};
    ld x=(d*d+c1.r*c1.r-c2.r*c2.r)/(2*d);
    Point v=(c2.c-c1.c)*Point(0,1);
    ld l=sqrtl(max<ld>(c1.r*c1.r-x*x,0.0l));
    v*=l/v.abs();
    Point p1=c1.c*(d-x)/d+c2.c*x/d+v;
    Point p2=c1.c*(d-x)/d+c2.c*x/d-v;
    if(dif==0){
        return {1,p1,p2};
    }
    if(sum==0){
        return {3,p1,p2};
    }
    return {2,p1,p2};
}
template<class Point>
Point Projection(Line<Point>l,Point p){
    static_assert(!is_integral_v<typename Point::Ptype>);
    using P=typename Point::Ptype;
    P t=(p-l.a).Dot(l.b-l.a)/(l.b-l.a).Dot(l.b-l.a);
    return l.a+(l.b-l.a)*t;
} 
template<class Point>
Point Reflecton(Line<Point>l,Point p){
    Point m=Projection(l,p);
    return 2*m-p;
}
template<class Point>
//時計回りなら負になる
typename Point::Ptype Area(vc<Point>p){
    if(p.size()<=2)return 0;
    typename Point::Ptype res=0;
    rep(i,p.size()){
        res+=p[i].Cross(p[(i+1)%p.size()]);
    }
    res/=2;
    return res;
}
template<class Point>
int Contain(vc<Point>g,Point p){
    assert(g.size()>=2);
    int in=0;
    rep(i,g.size()){
        auto a=g[i];
        auto b=g[(i+1)%g.size()];
        if((b-a).Cross(p-a)==0&&(p-a).Dot(p-b)<=0){
            return 1;
        }
        if(a.y>b.y)swap(a,b);
        if(a.y<=p.y&&p.y<b.y){
            if((b-a).Cross(p-a)<0)in^=1;
        }
    }
    return in*2;
}
template<class Point>
bool IsConvex(vc<Point>p){
    int sig=-1e9;
    rep(i,p.size()){
        Point a=p[i];
        Point b=p[(i+1)%p.size()];
        Point c=p[(i+2)%p.size()];
        int now_sign=sign((b-a).Cross(c-b));
        if(now_sign==0)continue;
        if(sig==-1e9)sig=now_sign;
        else if(sig!=now_sign)return 0;
    }
    return 1;
}
template<class Point>
tuple<ld,int,int>DiameterConvex(vc<Point>p){
    if(p.size()<=1)return {0,0,0};
    auto dist2=[&](int i,int j){
        auto q=p[i]-p[j];
        if constexpr(is_integral_v<typename Point::Ptype>){
            return (i128)q.x*q.x+(i128)q.y*q.y;
        }else{
            return q.Dot(q);
        }
    };
    auto res=make_tuple(dist2(0,0),0,0);
    auto update=[&](int i,int j){
        chmax(res,make_tuple(dist2(i,j),i,j));
    };
    int dir=0;
    rep(i,p.size()){
        int ni=(i+1)%p.size();
        int nni=(i+2)%p.size();
        dir=sign((p[ni]-p[i]).Cross(p[nni]-p[ni]));
        if(dir)break;
    }
    if(dir==0){
        int l=0,r=0;
        rep(i,p.size()){
            if(p[i].x<p[l].x||(p[i].x==p[l].x&&p[i].y<p[l].y))l=i;
            if(p[r].x<p[i].x||(p[r].x==p[i].x&&p[r].y<p[i].y))r=i;
        }
        update(l,r);
        return {sqrtl((ld)get<0>(res)),get<1>(res),get<2>(res)};
    }
    int j=1;
    rep(i,p.size()){
        int ni=(i+1)%p.size();
        while(1){
            int nj=(j+1)%p.size();
            auto cr=(p[ni]-p[i]).Cross(p[nj]-p[j]);
            if(sign(cr)*dir>0)j=nj;
            else break;
        }
        update(i,j);
        update(ni,j);
    }
    return {sqrtl((ld)get<0>(res)),get<1>(res),get<2>(res)};
}
template<class Point>
tuple<ld,int,int>DiameterConvex(vc<pair<Point,int>>p){
    if(p.empty())return {0,0,0};
    if(p.size()==1)return {0,p[0].second,p[0].second};
    auto dist2=[&](int i,int j){
        auto q=p[i].first-p[j].first;
        if constexpr(is_integral_v<typename Point::Ptype>){
            return (i128)q.x*q.x+(i128)q.y*q.y;
        }else{
            return q.Dot(q);
        }
    };
    auto res=make_tuple(dist2(0,0),p[0].second,p[0].second);
    auto update=[&](int i,int j){
        chmax(res,make_tuple(dist2(i,j),p[i].second,p[j].second));
    };
    int dir=0;
    rep(i,p.size()){
        int ni=(i+1)%p.size();
        int nni=(i+2)%p.size();
        dir=sign((p[ni].first-p[i].first).Cross(p[nni].first-p[ni].first));
        if(dir)break;
    }
    if(dir==0){
        int l=0,r=0;
        rep(i,p.size()){
            if(p[i].first.x<p[l].first.x||(p[i].first.x==p[l].first.x&&p[i].first.y<p[l].first.y))l=i;
            if(p[r].first.x<p[i].first.x||(p[r].first.x==p[i].first.x&&p[r].first.y<p[i].first.y))r=i;
        }
        update(l,r);
        return {sqrtl((ld)get<0>(res)),get<1>(res),get<2>(res)};
    }
    int j=1;
    rep(i,p.size()){
        int ni=(i+1)%p.size();
        while(1){
            int nj=(j+1)%p.size();
            auto cr=(p[ni].first-p[i].first).Cross(p[nj].first-p[j].first);
            if(sign(cr)*dir>0)j=nj;
            else break;
        }
        update(i,j);
        update(ni,j);
    }
    return {sqrtl((ld)get<0>(res)),get<1>(res),get<2>(res)};
}
template<class Point>
tuple<ld,int,int>FarthestPoint(vc<Point>p){
    assert(p.size()>=2);
    auto hull=ConvexHullIndex(p);
    if(hull.size()==1)return {0,0,1};
    return DiameterConvex(hull);
}
template<class Point>
Circle<Point>MinEnclosingCircle(vc<Point>p){
    mt19937 mt(random_device{}());
    shuffle(all(p),mt);
    if(p.empty())return {{0,0},0};
    Circle<Point>c{p[0],0};
    REP(i,1,p.size()){
        if(c.Contain(p[i]))continue;
        c={p[i],0};
        rep(j,i){
            if(c.Contain(p[j]))continue;
            c={(p[i]+p[j])/2,(p[i]-p[j]).abs()/2};
            rep(k,j){
                if(c.Contain(p[k]))continue;
                Line<Point>l1{(p[i]+p[j])/2,(p[i]+p[j])/2+(p[j]-p[i])*Point(0,1)};
                Line<Point>l2{(p[i]+p[k])/2,(p[i]+p[k])/2+(p[k]-p[i])*Point(0,1)};
                Point M=LLInter(l1,l2).second;
                c={M,(M-p[i]).abs()};
            }
        }
    }
    return c;
}

template<class Point>
Circle<Point>Incentor(Point a,Point b,Point c){
    ld S2=abs((b-a).Cross(c-a));
    ld SA=(b-a).abs()+(c-a).abs()+(c-b).abs();
    ld r=S2/SA;
    Point C=a*(b-c).abs()+b*(a-c).abs()+c*(b-a).abs();C/=SA;
    return {C,r};
}
template<class Point>
Circle<Point>Circumcenter(Point a,Point b,Point c){
    Line<Point>l1{(a+b)/2,(a+b)/2+(b-a)*Point(0,1)};
    Line<Point>l2{(a+c)/2,(a+c)/2+(c-a)*Point(0,1)};
    Point M=LLInter(l1,l2).second;
    return{M,(M-a).abs()};
}

//内部にある場合は壊れる
template<class Point>
pair<Point,Point>TangentToCircle(Circle<Point>C,Point a){
    ld d=(C.c-a).abs();
    ld r=C.r;
    ld V=sqrtl(max<ld>(0.0,d*d-r*r));
    Point e=(C.c-a)/d;
    ld theta=asin(r/d);
    return{a+V*e*Point(cos(theta),sin(theta)),a+V*e*Point(cos(-theta),sin(-theta))};
}
template<class Point>
vc<Point>CommonLine(Circle<Point>C1,Circle<Point>C2){
    vc<Point>res;
    for(auto&d:{-1,1}){
        Circle<Point>NC2{C2.c,abs(C2.r-d*C1.r)};
        ld dist=(NC2.c-C1.c).abs();
        int sig=sign(dist-NC2.r);
        if(sig<0)continue;
        vc<Point>us;
        if(sig==0)us.pb((NC2.c-C1.c)*Point(0,1));
        else{
            auto P=TangentToCircle(NC2,C1.c);
            us.pb(P.first-C1.c);
            us.pb(P.second-C1.c);
        }
        for(auto&u:us){
            if(sign(u.abs())==0)continue;
            Point e=u*Point(0,1);
            e/=e.abs();
            e*=C1.r;
            rep(f,2){
                Point nc1=e+C1.c;
                Point nc2=nc1+u;
                if(sign(LPdist({nc1,nc2},C2.c)-C2.r)==0){
                    res.pb(nc1);
                }
                e*=-1;
            }
        }
    }

    sort(all(res),[&](auto a,auto b){
        if(sign(a.x-b.x)!=0)return a.x<b.x;
        return a.y<b.y;
    });
    vc<Point>ans;
    for(auto p:res){
        if(ans.empty()||sign((p-ans.back()).abs())!=0){
            ans.pb(p);
        }
    }
    return ans;
}
template<class Point>
ld AreaCP(vc<Point>polygon,Circle<Point>C){
    for(auto&x:polygon)x-=C.c;
    C.c={0,0};
    ld res=0;
    rep(i,polygon.size()){
        Point a=polygon[i];
        Point b=polygon[(i+1)%polygon.size()];
        vc<ld>ts{0,1};
        ld A=(b-a).Dot(b-a);
        ld B=2*(b-a).Dot(a);
        ld C_=a.Dot(a)-C.r*C.r;
        ld D=B*B-4*A*C_;
        if(sign(D)>=0){
            ld T1=(-B+sqrtl(B*B-4*A*C_))/(2*A);
            ld T2=(-B-sqrtl(B*B-4*A*C_))/(2*A);
            if(0<=T1&&T1<=1)ts.pb(T1);
            if(sign(D)>0&&0<=T2&&T2<=1)ts.pb(T2);
        }
        sort(all(ts));
        rep(i,ts.size()-1){
            Point u=a+(b-a)*ts[i];
            Point v=a+(b-a)*ts[i+1];
            Point m=(u+v)/2;
            if(C.Contain(m)){
                res+=(u-C.c).Cross(v-C.c)/2;
            }else{
                res+=C.r*C.r*atan2(u.Cross(v),u.Dot(v))/2;
            }
        }
    }
    return res;
}
template<class Point>
ld AreaCC(Circle<Point>C1,Circle<Point>C2){
    if(C1.r>C2.r)swap(C1,C2);
    ld d=sqrtl((C1.c-C2.c).Dot(C1.c-C2.c));
    int S=sign(d-C1.r-C2.r);
    if(S>=0)return 0;
    int S2=sign(d-(C2.r-C1.r));
    if(S2<=0){
        return C1.r*C1.r*acos(-1);
    }
    ld theta1=acos((d*d+C1.r*C1.r-C2.r*C2.r)/(2*d*C1.r));
    ld theta2=acos((d*d+C2.r*C2.r-C1.r*C1.r)/(2*d*C2.r));
    return C1.r*C1.r*(theta1-sinl(theta1)*cosl(theta1))+
    C2.r*C2.r*(theta2-sinl(theta2)*cosl(theta2));
}
template<class Point>
vc<Point>CutPolygon(vc<Point>Polygon,Line<Point>l){
    vc<Point>res;
    Point v=(l.b-l.a);
    rep(i,Polygon.size()){
        Point A=Polygon[i];
        Point B=Polygon[(i+1)%Polygon.size()];
        bool ia=v.Cross(A-l.a)>=0;
        bool ib=v.Cross(B-l.a)>=0;
        if(ia&&ib){
            res.pb(B);
        }else if(!ia&&ib){
            typename Point::Ptype u=(l.a-A).Cross(v)/(B-A).Cross(v);
            Point D=A+(B-A)*u;
            res.pb(D);
            res.pb(B);
        }else if(ia&&!ib){
            typename Point::Ptype u=(l.a-A).Cross(v)/(B-A).Cross(v);
            Point D=A+(B-A)*u;
            res.pb(D);
        }
    }
    return res;
}
