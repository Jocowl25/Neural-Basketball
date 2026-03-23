#ifndef DATA_H
#define DATA_H
#include <array>
#include <string>
#include <iostream>
class Node{
    public:
        Node(std::string& line);

        double eval(const Node& other) const;

        double getResult() const{
            return result;
        }

        void update(const Node& other, int pos);

       friend std::ostream& operator<<(std::ostream& out, const Node &d);

    private:
        static const int size=7;
        std::array<double,size> input;
        double result;
};
#endif