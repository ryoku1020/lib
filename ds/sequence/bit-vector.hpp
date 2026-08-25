#pragma once
//n<=2^32
struct BitVector{
    using u64=uint64_t;
    vc<u64>big_block;
    vc<u64>pattern;
    constexpr static inline int B=64;
    int n;
    BitVector()=default;
    BitVector(const vc<int>&v):n(v.size()){
        big_block.assign((n+B-1)/B+1,0);
        pattern.assign(big_block.size()+1,0);
        REP(i,1,big_block.size()){
            u64 val=0;
            uint shift=0;
            uint lim=min<uint>(v.size(),i*B);
            REP(l,(i-1)*B,lim){
                assert(v[l]==0||v[l]==1);
                val+=(u64)v[l]<<(shift++);
            }
            big_block[i]=big_block[i-1]+__builtin_popcountll(val);
            pattern[i-1]=val;
        }
    }
    //[0,r)
    int rank1(int r)const{
        assert(0<=r&&r<=n);
        int res=big_block[r/B];
        res+=__builtin_popcountll(pattern[r/B]&((u64(1)<<(r%B))-1));
        return res;
    }
    int rank1(int l,int r)const{
        assert(0<=l&&l<=r&&r<=n);
        return rank1(r)-rank1(l);
    }
    int rank0(int r)const{
        assert(0<=r&&r<=n);
        return r-rank1(r);
    }
    int rank0(int l,int r)const{
        assert(0<=l&&l<=r&&r<=n);
        return r-l-rank1(l,r);
    }
};
