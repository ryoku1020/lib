#pragma once
template<class mint>
struct modint_vp{
    mint x=0;
    ll v=0;
    modint_vp()=default;
    modint_vp(ll a){*this=a;}
    static ll cut(ll&a){ll c=0;while(a&&a%mint::get_mod()==0)a/=mint::get_mod(),c++;return c;}
    modint_vp&operator=(ll a){v=0;if(!a)return x=0,*this;v=cut(a);x=a;return *this;}
    modint_vp&operator*=(ll a){if(!a)return x=0,v=0,*this;if(x==0)return *this;v+=cut(a);x*=a;return *this;}
    modint_vp&operator/=(ll a){assert(a);if(x==0)return *this;v-=cut(a);x/=a;return *this;}
    friend modint_vp operator*(modint_vp a,ll b){return a*=b;}
    friend modint_vp operator/(modint_vp a,ll b){return a/=b;}
    mint val()const{assert(v>=0);return v?0:x;}
};