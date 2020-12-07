#include <iostream>
#include "App.h"


App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){

    // Pushing different kinds of Shape in the collection
    // shapes.push_back(new TexRect("lion.png", -1, 1, 2, 2));
    // shapes.push_back(new Rect());
    // shapes.push_back(new Circle());

    
} 

void App::draw() const {
    // for(auto i = shapes.begin(); i != shapes.end(); i++){
    //     (*i)->draw();
    // }
    gm.draw();
}

void App::keyDown(unsigned char key, float x, float y){
    // std::cout<<key<<std::endl;

    switch(key){
        case 27:
            exit(0);
            break;

        default:
            gm.moveUpdate(key);
    }

    draw();

}

void App::idle() {
    // draw();
    gm.update();
}

App::~App(){   
    // for(auto i = shapes.begin(); i != shapes.end(); i++){
    //     delete *i;
    // }
    std::cout << "Exiting..." << std::endl;
}
