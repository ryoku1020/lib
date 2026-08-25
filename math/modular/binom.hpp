#pragma once
template<class,class=void>
struct binom_has_get_mod:false_type{};
template<class mint>
struct binom_has_get_mod<mint,void_t<decltype(mint::get_mod())>>:true_type{};
template<class mint>
struct binom{
private:
    static vector<mint>&fact_table(){static vector<mint>v={1};return v;}
    static vector<mint>&invfact_table(){static vector<mint>v={1};return v;}
    static vector<mint>&invs_table(){static vector<mint>v={0};return v;}
    static int&built_mod(){static int mod=-1;return mod;}
public:
    static void build(int n){
        auto&_fact=fact_table();
        auto&_invfact=invfact_table();
        auto&_invs=invs_table();
        if constexpr(binom_has_get_mod<mint>::value){
            auto mod=mint::get_mod();
            if(built_mod()!=mod){
                _fact={1};
                _invfact={1};
                _invs={0};
                built_mod()=mod;
            }
        }
        if(n<(int)_fact.size())return;
        int old=_fact.size();
        _fact.resize(n+1);
        _invfact.resize(n+1);
        _invs.resize(n+1);
        if constexpr(binom_has_get_mod<mint>::value){
            auto mod=mint::get_mod();
            for(int i=old;i<=n;i++){
                _fact[i]=_fact[i-1]*i;
                if(i==1)_invs[i]=1;
                else _invs[i]=-_invs[mod%i]*(mod/i);
                _invfact[i]=_invfact[i-1]*_invs[i];
            }
        }else{
            for(int i=old;i<=n;i++){
                _fact[i]=_fact[i-1]*i;
                _invs[i]=mint(1)/i;
                _invfact[i]=_invfact[i-1]*_invs[i];
            }
        }
    }
    static mint fact(int i){
        assert(i>=0);
        build(i);
        return fact_table()[i];
    }
    static mint invfact(int i){
        assert(i>=0);
        build(i);
        return invfact_table()[i];
    }
    static mint inv(int i){
        assert(i>0);
        build(i);
        return invs_table()[i];
    }
    static mint C(int a,int b){//aCb
        if(b==0)return 1;
        if(a<0||b<0||a-b<0)return mint(0);
        build(a);
        auto&_fact=fact_table();
        auto&_invfact=invfact_table();
        return _fact[a]*_invfact[b]*_invfact[a-b];
    }
    static mint iC(int a,int b){//1/aCb
        if(b==0)return 1;
        if(a<0||b<0||a-b<0)return mint(0);
        build(a);
        auto&_fact=fact_table();
        auto&_invfact=invfact_table();
        return _fact[b]*_fact[a-b]*_invfact[a];
    }
    static mint P(int a,int b){
        if(a<b||b<0)return 0;
        build(a);
        auto&_fact=fact_table();
        auto&_invfact=invfact_table();
        return _fact[a]*_invfact[a-b];
    }
    static mint H(int a,int b){
        return C(a+b-1,b);
    }

};