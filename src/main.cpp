#include <iostream>
#include <FlowNetwork.h>


int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    std::cout << "/////////////// Task 1 ///////////////" << std::endl;
    FlowNetwork flowNetwork(4);
    flowNetwork.Print();
    flowNetwork.Draw();

    return 0;
}