#pragma once
struct barrett{
    using u64=uint64_t;
    using u32=uint32_t;
    using i128=__int128_t;
    u64 m;
    int mod;
    void set(int mod_){
        assert(mod_>0);
        mod=mod_;
        m=(i128(1)<<64)/mod;
    }
    unsigned reduce(uint64_t x){
        assert(mod>0);
        x-=(((i128)x*m)>>64)*mod;
        return x<mod?x:x-mod;
    }
};
