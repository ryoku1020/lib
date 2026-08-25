#pragma once
template<class mint,int N=32>
vc<mint>subset_convolution(vc<mint>f,vc<mint>g){
    assert(f.size()==g.size());
    assert((1<<tbit(f.size()))==f.size());
    if constexpr(N<32){
        constexpr int W=N+1;
        int m=1<<N;
        auto add=[&](auto&A,int i,int j,int c){
            mint*a=A.data()+i*W;
            mint*b=A.data()+j*W;
            rep(k,c+1)a[k]+=b[k];
        };
        auto sub=[&](auto&A,int i,int j,int c){
            mint*a=A.data()+i*W;
            mint*b=A.data()+j*W;
            for(int k=c;k<=N;k++)a[k]-=b[k];
        };
        auto mul=[&](auto&A,auto&B,int p,int c){
            mint res[W]{};
            mint*a=A.data()+p*W;
            mint*b=B.data()+p*W;
            int lim=min(N,c+c);
            for(int k=c;k<=lim;k++){
                mint x=0;
                int L=max(0,k-c),R=min(c,k);
                for(int i=L;i<=R;i++){
                    x+=a[i]*b[k-i];
                }
                res[k]=x;
            }
            for(int k=c;k<=N;k++)a[k]=res[k];
        };

        assert(max(g.size(),f.size())<=m);
        vc<int>pc(m);
        rep(i,m)pc[i]=popcount(i);
        
        vc<mint>F(m*W),G(m*W);
        rep(i,f.size())F[i*W+pc[i]]=f[i];
        rep(j,g.size())G[j*W+pc[j]]=g[j];
        
        rep(j,N){
            int w=1<<j;
            for(int b=0;b<m;b+=w<<1){
                rep(t,w){
                    int i=b+w+t;
                    add(F,i,i^w,pc[i^w]);
                }
            }
        }
        rep(j,N){
            int w=1<<j;
            for(int b=0;b<m;b+=w<<1){
                rep(t,w){
                    int i=b+w+t;
                    add(G,i,i^w,pc[i^w]);
                }
            }
        }

        rep(i,m)mul(F,G,i,pc[i]);

        drep(j,N){
            int w=1<<j;
            for(int b=0;b<m;b+=w<<1){
                rep(t,w){
                    int i=b+w+t;
                    sub(F,i,i^w,pc[i]);
                }
            }
        }

        vc<mint>res(m);
        rep(i,m)
            res[i]=F[i*W+pc[i]];

        res.resize(f.size());
        return res;
    }else{
        vc<mint>ans;
        switch(tbit(f.size())){
            case 0:ans=subset_convolution<mint,0>(f,g);break;
            case 1:ans=subset_convolution<mint,1>(f,g);break;
            case 2:ans=subset_convolution<mint,2>(f,g);break;
            case 3:ans=subset_convolution<mint,3>(f,g);break;
            case 4:ans=subset_convolution<mint,4>(f,g);break;
            case 5:ans=subset_convolution<mint,5>(f,g);break;
            case 6:ans=subset_convolution<mint,6>(f,g);break;
            case 7:ans=subset_convolution<mint,7>(f,g);break;
            case 8:ans=subset_convolution<mint,8>(f,g);break;
            case 9:ans=subset_convolution<mint,9>(f,g);break;
            case 10:ans=subset_convolution<mint,10>(f,g);break;
            case 11:ans=subset_convolution<mint,11>(f,g);break;
            case 12:ans=subset_convolution<mint,12>(f,g);break;
            case 13:ans=subset_convolution<mint,13>(f,g);break;
            case 14:ans=subset_convolution<mint,14>(f,g);break;
            case 15:ans=subset_convolution<mint,15>(f,g);break;
            case 16:ans=subset_convolution<mint,16>(f,g);break;
            case 17:ans=subset_convolution<mint,17>(f,g);break;
            case 18:ans=subset_convolution<mint,18>(f,g);break;
            case 19:ans=subset_convolution<mint,19>(f,g);break;
            case 20:ans=subset_convolution<mint,20>(f,g);break;
            case 21:ans=subset_convolution<mint,21>(f,g);break;
            case 22:ans=subset_convolution<mint,22>(f,g);break;
            case 23:ans=subset_convolution<mint,23>(f,g);break;

        }
        return ans;
    }
}
