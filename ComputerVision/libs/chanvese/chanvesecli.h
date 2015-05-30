
/** @brief Program parameters struct */
typedef struct
{
    /** @brief Input file name */
    //MODIFIED BY GARO: re-put a const
    char *InputFile;
    /** @brief Animation output file name */
    const char *OutputFile;
    /** @brief Binary output file name */
    const char *OutputFile2;
    /** @brief Quality for saving JPEG images (0 to 100) */
    int JpegQuality;
  
    /** @brief Level set */
    image Phi;
    /** @brief ChanVese options object */
    chanveseopt *Opt;
    
    int IterPerFrame;
} programparams;

/** @brief Plotting parameters struct */
typedef struct
{
    const float *Image;
    unsigned char *Plot;
    int *Delays;
    int IterPerFrame;
    int NumFrames;
} plotparam;

int ParseParam(programparams *Param, int argc, const char *argv[]);
int PhiRescale(image *Phi);

int WriteBinary(image Phi, float *Temp);
int SetParam(programparams *Param, float *Contour, image *input);
