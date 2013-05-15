#include <stdlib.h>
#include <AL/alut.h>
 
 int
 main (int argc, char **argv)
{
    ALuint helloBuffer, helloSource;
    alutInit (&argc, argv);
    helloBuffer = alutCreateBufferHelloWorld ();
    alGenSources (1, &helloSource);
    alSourcei (helloSource, AL_BUFFER, helloBuffer);
    alSourcePlay (helloSource);
    alutSleep (1);
    alutExit ();
    
    return EXIT_SUCCESS;
}
