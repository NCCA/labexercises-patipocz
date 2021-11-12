#include <iostream>
#include <cstdlib>
#include "Walker.h"
#include <fmt/format.h>

int main()
{
    std::cout<<"DLA!\n";
    Walker w(200,200);
    w.setImageSeed(0,0);

    for(int i=0; i<20; ++i)
        w.randomImageSeed();



    int iterations = 1000;
    int simCount=0;
    int imageIndex=0;
    for(int i=0; i<iterations; ++i)
    {
        if(w.walk() == true)
        {
            if(!(simCount++ %100))
                w.saveImage(fmt::format("sim{:064d}.exr",imageIndex++));
        }
        w.resetStart();
    }            
    w.saveImage("test.exr");
    return EXIT_SUCCESS;

}