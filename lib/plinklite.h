/*
    plinklite is lightwight library to read and write plink bed file.

    -Benjamin Fang 20230214
*/

#ifndef PLINKLITE_HEAD
#define PLINKLITE_HEAD

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#if !defined PLINKLITE_SRC
#define PLINKLITE_EXTERN extern
#else
#define PLINKLITE_EXTERN
#endif


#define CharM1 0x03
#define CharM2 0x0c
#define CharM3 0x30
#define CONVERT_GENO(x) ((x) == 0) ? 2 : (((x) == 2) ? 1 : (((x) == 3) ? 0 : 4))

#define PLINK_OPEN_SUCCESS 0
#define PLINK_OPEN_FAIL 5
#define PLINK_FILE_OPEN_FAIL 1
#define PLINK_FILE_EMPTY 2
#define PLINK_MEGIC_NUM_FAIL 3
#define PLINK_MALLOC_BUF_FAIL 4
#define PLINK_MEGIC_NUM_LEN 3
#define PLINK_LINE_BUF_LEN 2048

typedef struct plinkfile {
    uint32_t individual_num;
    uint32_t variant_num;

    uint32_t current_fam_line_index;
    uint32_t current_bim_line_index;
    uint32_t current_bed_data_index;

    FILE *fam_file;
    FILE *bim_file;
    FILE *bed_file;
    
    uint64_t fam_byte_offset;
    uint64_t bim_byte_offset;
    uint64_t bed_byte_offset;

    char bed_megic_num[3];
    uint32_t raw_buf_len;
    char *bed_raw_per_variant_buf;
    uint32_t decode_buf_len;
    char *bed_decoded_per_variant_buf;
    char *line_buf;
    char status;

} PLINKFILE, *PLINKFILE_ptr;


#define PLINK_FAM_NA 0

typedef struct fam_line {
    char family_id[64];
    char within_famid[64];
    char father_id[64];
    char mother_id[64];
    char sex;
    char phenotype_value;

} FAM_LINE, *FAM_LINE_ptr;

#define PLINK_MISSING_CHROM 0
#define PLINK_X_CHROM 201
#define PLINK_Y_CHROM 202
#define PLINK_MT_CHROM 203
#define PLINE_BIM_POS_NA 0
#define PLINE_MAX_ALLEL_LEN 8
typedef struct bim_line {
    unsigned char chrom;
    char rsid[64];
    float phy_pos;
    uint32_t pos;
    char allel1[PLINE_MAX_ALLEL_LEN];
    char allel2[PLINE_MAX_ALLEL_LEN];

} BIM_LINE, *BIM_LINE_ptr;

PLINKLITE_EXTERN PLINKFILE plinkopen(const char *filename);
PLINKLITE_EXTERN void plinkclose(PLINKFILE plink_data);

PLINKLITE_EXTERN int famreadline(PLINKFILE plink_data, FAM_LINE_ptr fam_line);
PLINKLITE_EXTERN int famreadlines(PLINKFILE plink_data, FAM_LINE_ptr fam_lines,
                                  uint32_t fam_line_num);

PLINKLITE_EXTERN int bimreadline(PLINKFILE plink_dara, BIM_LINE_ptr bim_line);

PLINKLITE_EXTERN int bimreadlines(PLINKFILE plink_data, BIM_LINE_ptr bim_lines,
                                  int bim_line_num);

PLINKLITE_EXTERN int bedreaddata(PLINKFILE plink_data, char *bed_data,
                                 int bed_data_len);

PLINKLITE_EXTERN int bedloaddata_n(PLINKFILE plink_data, char *bed_data,
                                   size_t bed_data_len, int start, int end);

PLINKLITE_EXTERN int bedloaddata_all(PLINKFILE plink_data, char *bed_data,
                                     size_t bed_data_len);
#endif


