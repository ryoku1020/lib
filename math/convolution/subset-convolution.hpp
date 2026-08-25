#pragma once
template<class mint,int N=32>
vc<mint>SubsetConvolution(vc<mint>f,vc<mint>g){
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
            case 0:ans=SubsetConvolution<mint,0>(f,g);break;
            case 1:ans=SubsetConvolution<mint,1>(f,g);break;
            case 2:ans=SubsetConvolution<mint,2>(f,g);break;
            case 3:ans=SubsetConvolution<mint,3>(f,g);break;
            case 4:ans=SubsetConvolution<mint,4>(f,g);break;
            case 5:ans=SubsetConvolution<mint,5>(f,g);break;
            case 6:ans=SubsetConvolution<mint,6>(f,g);break;
            case 7:ans=SubsetConvolution<mint,7>(f,g);break;
            case 8:ans=SubsetConvolution<mint,8>(f,g);break;
            case 9:ans=SubsetConvolution<mint,9>(f,g);break;
            case 10:ans=SubsetConvolution<mint,10>(f,g);break;
            case 11:ans=SubsetConvolution<mint,11>(f,g);break;
            case 12:ans=SubsetConvolution<mint,12>(f,g);break;
            case 13:ans=SubsetConvolution<mint,13>(f,g);break;
            case 14:ans=SubsetConvolution<mint,14>(f,g);break;
            case 15:ans=SubsetConvolution<mint,15>(f,g);break;
            case 16:ans=SubsetConvolution<mint,16>(f,g);break;
            case 17:ans=SubsetConvolution<mint,17>(f,g);break;
            case 18:ans=SubsetConvolution<mint,18>(f,g);break;
            case 19:ans=SubsetConvolution<mint,19>(f,g);break;
            case 20:ans=SubsetConvolution<mint,20>(f,g);break;
            case 21:ans=SubsetConvolution<mint,21>(f,g);break;
            case 22:ans=SubsetConvolution<mint,22>(f,g);break;
            case 23:ans=SubsetConvolution<mint,23>(f,g);break;

        }
        return ans;
    }
}