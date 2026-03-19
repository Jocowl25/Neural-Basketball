#include "Node.h"
#include <sstream>
#include <cassert>
Node::Node(std::string& line){
     std::stringstream stream(line);
     std::string word;
     for(int i=0;i<6;i++){
        stream>>word;
        input[i]=std::stod(word);
     }
     if(stream>>word){
     result=std::stod(word);
     }else{
        result=0;
     }
}

double Node::eval(const Node& other) const{
    double total;
    //Dot product
    for(unsigned int i=0;i<6;++i){
        total+=input[i]*other.input[i];
    }
    //Step function
    if(total<0){
        total=-1;
    }else{
        total=1;
    }
    return total;
}

void Node::update(const Node& other,int pos){
    for(unsigned int i=0;i<6;++i){
        input[i]+=pos*other.input[i];
    }
}

std::ostream& operator<<(std::ostream& out, const Node &d){
        out<<"Weights: ";
        for(unsigned int i=0;i<6;i++){
            out<<d.input[i]<<" ";
        }
        out<<"\n\n";
        return out;
}
