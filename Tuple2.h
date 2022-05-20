//
// Created by Nir on 29/11/2021.
//

#ifndef WET1_TUPLE2_H
#define WET1_TUPLE2_H

template<class T,class S>
class Tuple2 {
    T value1;
    S value2;
public:
    Tuple2(const T& value1, const S& value2): value1(value1), value2(value2) {}
    Tuple2() = default;
    ~Tuple2() = default;
    Tuple2(const Tuple2& t) = default;
    const T getValue1() const;
    const S getValue2() const;
    bool operator<(const Tuple2<T,S>& t) const;
    bool operator>(const Tuple2<T,S>& t) const;
    bool operator==(const Tuple2<T,S>& t) const;
    bool operator!=(const Tuple2<T,S>& t) const;
};

template<class T, class S>
const T Tuple2<T, S>::getValue1() const{
    return value1;
}

template<class T, class S>
const S Tuple2<T, S>::getValue2() const{
    return value2;
}

template<class T, class S>
bool Tuple2<T, S>::operator<(const Tuple2<T, S> &t) const{
    if (this->value1 < t.value1){
        return true;
    }
    else if (this->value1 > t.value1){
        return false;
    }
    else{ //value1 equal
        if (this->value2>t.value2){
            return true;
        }
        else{
            return false;
        }
    }
}


template<class T, class S>
bool Tuple2<T, S>::operator==(const Tuple2<T, S> &t) const{
    if (this->value1 == t.value1 && this->value2 == t.value2){
        return true;
    }
    return false;
}

template<class T, class S>
bool Tuple2<T, S>::operator!=(const Tuple2<T, S> &t) const{
    return !(*this == t);
}


template<class T, class S>
bool Tuple2<T, S>::operator>(const Tuple2<T, S> &t) const{
    if (!(*this<t) && *this!=t){
        return true;
    }
    return false;
}



#endif //WET1_TUPLE2_H
