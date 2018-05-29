#include <iostream>
#include <FlowNetwork.h>


int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    std::cout << std::endl << "//////////////// Task 1 ///////////////" << std::endl;
    FlowNetwork flowNetwork(2);
    flowNetwork.Print();
    flowNetwork.Draw();
    std::cout << std::endl << "//////////////// Task 2 ///////////////" << std::endl;
    flowNetwork.FordFulkerson();

    return 0;
}