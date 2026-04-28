#include <fstream>
#include <string>
#include "Node.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

void training(Node& weights,std::string input){
    std::ifstream inpFile(input);
    std::string line;
    std::vector<Node> inputs;
   
    //add input file data into vector
    while(std::getline(inpFile,line)){
        const Node tmp(line);
        inputs.push_back(tmp);
    }

    double correct=0;
    std::cout<<"Progress: \n";
    double total=inputs.size();
    while(correct<total){
        correct=0;
        for(unsigned int i=0;i<total;i++){
            double prediction=weights.eval(inputs[i]);
            if(prediction!=inputs[i].getResult()){
                if(prediction==1){
                    weights.update(inputs[i],-1);
                }else{
                    weights.update(inputs[i],1);
                }
            }else{
                correct++;
            }
        }
        std::cout<<((correct/total)*100)<<"% ";
    }
    std::cout<<"\nTraining Done with "<<((correct/total)*100)<<"%\n";

    std::cout<<weights;
}

double testing(Node& weights,std::string input){
    double correct=0;
    std::ifstream inpFile(input);
    std::string line;
    std::vector<Node> inputs;
    
    //add input file data into vector
    while(std::getline(inpFile,line)){
        const Node tmp(line);
        inputs.push_back(tmp);
    }

    const double total=inputs.size();

    for(unsigned int i=0;i<inputs.size();i++){
        double prediction=weights.eval(inputs[i]);
        if(i<9){
            std::cout<<" ";
        }
        std::cout<<i+1<<": ";
        if(prediction!=inputs[i].getResult()){
            std::cout<<"Fail\n";
        }else{
            std::cout<<"Success\n";
            correct++;
        }
    }
    return (correct/total)*100;
}

//Generate random number from 0 to max (exclusive)
int randomNumInRange(int max){ 
    int r = std::rand();
    return r%max;
}

//Generate string of count random numbers, separated by a space
std::string randomNumString(int count){
    std::string output="";
    for(int i=0;i<count;++i){
        output+=std::to_string(randomNumInRange(2))+" ";
    }
    return output;
}

int main(int argc, char* args[]){
    std::srand(std::time(0));
    
    double secondVal=randomNumInRange(3);
    if(secondVal==2){
        secondVal=0.5;
    }
    std::string secValStr=std::to_string(secondVal)+" ";

    std::string start=randomNumString(1)+secValStr+randomNumString(5);
    Node weights(start);
    std::cout<<"Initialization\n"<<weights;
    std::cout<<"Starting training\n";
    training(weights,"training.txt");
    std::cout<<"Correctness:\n"<<testing(weights,"testing.txt")<<"%\n\n";


    std::string finalTestData="0 1 0 1 0 0 1 1 1";
    Node finalTest(finalTestData);
    std::cout<<"---------\n";
    std::cout<<"Checking "+finalTestData<<"\n";
    std::cout<<"Result: This game is a ";
    if(weights.eval(finalTest)==1){
        std::cout<<"Win\n";
    }else if(weights.eval(finalTest)==-1){
        std::cout<<"Loss\n";
    }else{
        std::cout<<"????\n";
    }
    std::cout<<"---------\n";
    return 0;
}