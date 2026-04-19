#ifndef IG20260323011843
#define IG20260323011843

typedef struct
{
    char* input;
    char* options;
} Prompt;

/// Return initialized prompt object
Prompt newPrompt( void );

#endif
