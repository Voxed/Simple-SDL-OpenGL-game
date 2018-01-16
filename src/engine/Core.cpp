#include "Core.h"

Core::Core() 
{
    int sdlErrorCode = Core::initSDL();
    if( sdlErrorCode == 0 )
    {
        int windowErrorCode = Core::initWindow();
        if( windowErrorCode == 0 )
        {
            int glErrorCode = Core::initGL();
            if( glErrorCode == 0)
            {
                printf( "Core initialization complete\n" );
                return;
            }
        }
    }
    error = true;
}

Core::~Core()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Core::hasError()
{
    return error;
}

int Core::initSDL()
{
    int errorCode = SDL_Init( SDL_INIT_VIDEO );
    if( errorCode != 0 )
    {
        printf( "Could not initialize SDL!\nError: %s\n", SDL_GetError() );
        return -1;
    }
    return 0;
}

int Core::initWindow()
{
    window = SDL_CreateWindow(
        "Title",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_OPENGL
    );
    if( window == NULL )
    {
        printf( "Could not initialize window!\nError: %s\n", SDL_GetError() );
        return -1;
    }
    return 0;
}

int Core::initGL()
{
    context = SDL_GL_CreateContext( window );
    if( context == NULL )
    {
        printf( "Could not initialize GL context!\nError: %s\n", SDL_GetError() );
        return -1;
    }

    GLenum glewError = glewInit();
    if( glewError != GLEW_NO_ERROR )
    {
        printf( "Could not intialize GLEW!\nError: %s\n", glewGetErrorString(glewError));
        return -1;
    }

    int flags = IMG_INIT_PNG;
    int inittedFlags = IMG_Init( flags );
    if( inittedFlags&flags != flags )
    {
        printf( "Could not initialize SDL-image!\nError: %s\n", IMG_GetError());
        return -1;
    }
    return 0;
}

int Core::start()
{
    Logic l = Logic(this);
    Graphics g = Graphics(this, l);
    started = true;

    //Main loop :)
    bool quit = false;
    SDL_Event e;
    std::vector<int> held_keys = std::vector<int>();
    while( !quit )
    {
        while( SDL_PollEvent(&e) )
        {
            switch( e.type ) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if(std::find(held_keys.begin(), held_keys.end(), e.key.keysym.sym) == held_keys.end())
                    {
                        for(auto const& action : Keyboard::getActions(e.key.keysym.sym))
                        {
                            Action a;
                            a.action = action;
                            a.type = ActionType::KEYBOARD;
                            a.state = ActionState::PRESSED;
                            Actions::call(a);
                        }
                        held_keys.push_back(e.key.keysym.sym);
                    }
                    break;
                case SDL_KEYUP:
                    for(auto const& action : Keyboard::getActions(e.key.keysym.sym))
                    {
                        Action a; 
                        a.type = ActionType::KEYBOARD;
                        a.state = ActionState::RELEASED;
                        Actions::call(a);
                    }
                    held_keys.erase(std::remove(held_keys.begin(), held_keys.end(), e.key.keysym.sym), held_keys.end()); 
                    break;
            }
        }
        for(auto key : held_keys)
        {   
            for(auto const& action : Keyboard::getActions(key))
            {
                Action a;
                a.action = action;
                a.type = ActionType::KEYBOARD;
                a.state = ActionState::HELD;
                Actions::call(a);
            }
        }

        g.render();
        l.update(1.0f);
        SDL_GL_SwapWindow(window);

        SDL_Delay(60/1000);
    }
}

void Core::setScreen(Screen * scr)
{
    scr->core = this;
    this->scr = scr;
}

Screen * Core::getScreen()
{
    return scr;
}

bool Core::hasStarted()
{
    return started;
}