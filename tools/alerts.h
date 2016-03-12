// In that file, some macros for errors are defined

#ifndef ALERTS_H
#define ALERTS_H

#define DEBUGMODE

#ifdef DEBUGMODE

//for errors, caused by user. Normally thay must be implemented through ex's TODO(#1)
#define USERERR(...)\
    {\
        fprintf(stderr, __VA_ARGS__);\
        fflush(stderr);\
        exit(0);\
    }
     
/* Some errors that might be caused either by user, or by bugs, or by 'world', like allocation errors 
   they should be handled as well TODO(#1)*/
#define EXERR(...)\
    {\
        fprintf(stderr, "FATAL ERROR: " __VA_ARGS__);\
        fprintf(stderr, "\nFile: %s\nLine: %d\nFunction: %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);\
        fflush(stderr);\
        exit(1);\
    }

//Actually, that is the core of alerts.h. For debugging the code and getting maximum information.
#define ERR(...)\
    {\
        fprintf(stderr, "FATAL ERROR: " __VA_ARGS__);\
        fprintf(stderr, "\nFile: %s\nLine: %d\nFunction: %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);\
        fflush(stderr);\
        exit(1);\
    }

#define DBGPRINT(...)\
    {\
        printf(__VA_ARGS__);\
    }

#endif
#endif
