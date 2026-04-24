#pragma once
#include"../template.hpp"
template<class Point_type,Point_type eps=0>
struct Point{
    Point_type x,y;
    Point&operator+=(const Point&p){
        x+=p.x,y+=p.y;
        return *this;
    }
    Point&operator-=(const Point&p){
        x-=p.x,y-=p.y;
        return *this;
    }
    friend Point operator+(Point p1,const Point&p2){
        return Point(p1)+=p2;
    }
    friend Point operator-(Point p1,const Point&p2){
        return Point(p1)-=p2;
    }
    //res=0:90 res>0:less 90 res<0:bigger 90
    Point_type Dot(const Point&b){
        return x*b.x+y*b.y;
    }
    //res=0:平行 res>0:b が a からみて反時計回りの位置 res<0:逆
    Point_type Cross(const Point&b){
        return x*b.y-y*b.x;
    }
    bool operator==(const Point&p) const{
        return abs(p.x-x)<=eps&&abs(p.y-y)<=eps;
    }
    bool operator!=(const Point&p) const{
        return p.x==x&&p.y==y;
    }
    #ifdef LOCAL
    friend ostream&operator<<(ostream&os,const Point&f){
        os<<"("<<f.x<<","<<f.y<<")";
        return os;
    }
    #endif
};
template<class point>
pair<vc<point>,vc<point>>ConvexHull(vc<point> points){

    points.erase(unique(all(points)),points.end());
    if(points.size()<=2)return {points,points};
    sort(all(points),[&](auto a,auto b){
        if(a.x!=b.x)return a.x<b.x;
        return a.y<b.y;
    });
    vc<point>lower_convexhull{points[0],points[1]},upper_convexhull{points[points.size()-1],points[points.size()-2]};
    
    REP(i,2,points.size()){
        while(lower_convexhull.size()>=2){
            auto pb1=lower_convexhull.back();lower_convexhull.pop_back();
            auto pb2=lower_convexhull.back();
            if((pb1-pb2).Cross(points[i]-pb1)<=0){
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
            if((pb1-pb2).Cross(points[i]-pb1)<=0){
                continue;
            }
            upper_convexhull.push_back(pb1);break;
        }
        upper_convexhull.push_back(points[i]);
    }
    return {lower_convexhull,upper_convexhull};
}