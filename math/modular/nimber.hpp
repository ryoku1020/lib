#pragma once
struct nimber{
    static const int B=256;
    using u64=ull;
    inline static uint8_t ans[B][B];
    static u64 nimproduct(u64 a,u64 b,int w){
        if(w==1)return u64(a&b);
        uint au=a>>(w/2);uint av=a&((1ull<<(w/2))-1);
        uint bu=b>>(w/2);uint bv=b&((1ull<<(w/2))-1);
        u64 p=nimproduct(au,bu,w/2);
        u64 r=nimproduct(av,bv,w/2);
        u64 q=nimproduct(au^av,bu^bv,w/2)^p^r;
        return ((p^q)<<(w/2))^nimproduct(p,1ull<<(w/2-1),w/2)^r;
    }
    static void init(){
        rep(a,B)rep(b,B){
            ans[a][b]=nimproduct(a,b,8);
        }
    }
    ull val;
    template<int w>
    u64 nimp(u64 a,u64 b){
        if constexpr(w<=8)return ans[a][b];
        uint au=a>>(w/2);uint av=a&((1ull<<(w/2))-1);
        uint bu=b>>(w/2);uint bv=b&((1ull<<(w/2))-1);
        u64 p=nimp<w/2>(au,bu);
        u64 r=nimp<w/2>(av,bv);
        u64 q=nimp<w/2>(au^av,bu^bv)^p^r;
        return ((p^q)<<(w/2))^nimp<w/2>(p,1ull<<(w/2-1))^r;
    }
    nimber(u64 x=0):val(x){}
    nimber&operator*=(const nimber&rhs){
        return *this=nimber(nimp<64>(val,rhs.val));
    }
    nimber&operator+=(const nimber&rhs){
        val^=rhs.val;
        return *this;
    }
    friend nimber operator*(nimber lhs,nimber rhs){
        return lhs*=rhs;
    }
    friend nimber operator+(nimber lhs,nimber rhs){
        return lhs+=rhs;
    }
    nimber pow(ull n)const{
        nimber x=*this,res=1;
        while(n){
            if(n&1)res*=x;
            x*=x;
            n>>=1;
        }
        return res;
    }
    nimber inv()const{
        assert(val);
        return pow(~0ull-1);
    }
    nimber&operator/=(const nimber&rhs){
        return *this=nimber(nimp<64>(val,rhs.inv().val));
    }

    friend nimber operator/(nimber lhs,nimber rhs){
        return lhs/=rhs;
    }
};
struct nimberinit{
    nimberinit(){
        nimber::init();
    }
}nimberinit;