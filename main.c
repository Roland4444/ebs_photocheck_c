#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
    typedef struct{
        int major;
        int minor;
        int build;
    } Version;

    typedef struct{
        Version version;
        char *id;
        void *payment;
        int last_error;
    } Session;

    typedef int (*BKK)(Session *,  char *path_to_config);
    typedef int (*i_check_format)(Session *,  uint8_t * , uint64_t);

    typedef struct{
        int checkResult;
        int lastErrorInSession;
        int ResultLoadingSoSymbols;
    } ResultCheck;

    ResultCheck* lets_check(char * config, char * filename){
        ResultCheck* returned=(ResultCheck*)malloc(sizeof(ResultCheck));
        returned->ResultLoadingSoSymbols=0;
        returned->lastErrorInSession=0;
        returned->checkResult=0;
        void* handle = dlopen("./libBKKAdaptor.so", RTLD_NOW);
        if (!handle){
            printf("error load lib BKK");
            returned->ResultLoadingSoSymbols=1;
            return returned;
        }
        BKK load_ = (BKK)(dlsym(handle, "i_create_session"));
        if (!load_)
        {
            printf("error load symbol");
            returned->ResultLoadingSoSymbols=2;
            return returned;
        }
        Session sess;
        sess.id="my_session";
        if (!load_(&sess, config)){
                printf("error create session");
            returned->ResultLoadingSoSymbols=3;
            return returned;
        }
        uint8_t **content;
        uint8_t * direct;
        FILE *fd = fopen(filename, "rb");
        uint64_t *content_size;
        if (fd != NULL) {
            fseek(fd, 0L, SEEK_END);
            uint64_t size = ((size_t) ftell(fd) );
            content_size = & size;
            rewind(fd);
            uint8_t * pointer =(uint8_t *) calloc(1, (*content_size));
            direct = pointer;
            content = & pointer;
            fread((*content), (*content_size), 1, fd);
            fclose(fd);
        }
        else{
            printf("error read file");
            returned->ResultLoadingSoSymbols=4;
            return returned;
        }
        i_check_format load = (i_check_format)(dlsym(handle,"i_check_format"));
        if (!load) {
            printf("load check failed", sess.last_error);
            dlclose(handle);
            returned->ResultLoadingSoSymbols=5;
            return returned;
        }
        Session * pointSession = &sess;
        printf("\n\n\nlets check!!!\n\n\n");
        uint8_t result___ = load(pointSession, direct, *content_size);
        printf("CONTENT SIZE ==>> %u", content_size);
        printf("\nresult==>%u\n", result___);
        printf("\nlast_error==>%d\n", pointSession->last_error);

        return returned;

    };


int main()
{
	char * mass[]={"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/null_size.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/81A16FE30E67D812332CDEDA986281B41F59243082B792C13F0E004AF77BC0E0.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/0E1E34EB64FFF7379A83F6A14CDD40FA3375E94D5142FB27F9343F00FAFA4BDF.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/photo/photo-9fN3XP0T.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/photo/151-184-4650-1560791307-1469013564.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/0E6FAC5F3B4865A8DD2EBD47E88B5B26FA4ED3D34CB8C069F410E3714DDE8306.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/DBAE51A3CF1BFCDE278B1DFE786D37FA2EDD3C8C5A73D93ED779982777FFC47B.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/C9EE7150CCBD1E08D25F762044B96B65D90734454EC6D5482F433462E2C81AE5.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/8030CA32056C693DA881F344C9C45210516FAE1BF9ADA538714E0D4EC6F4ED66.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/this_is_PNG.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/6EBE2832E2B3504A709D92BE46EB3A1BC3BAF41A038D5E814C35CD89AB69906F.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/BBE44B0ACE1EA0418289050A9D4796C475DF29C759F30586B33A56B7B7762321.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/B697496EE1D8F0BD2177DB771EAB0A5B377B72C2F8DB10A1416678FED6F1F6CB.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/942885F2F8CC481B7187210E15E11517CF24D3A18E94C9464F64DE65BDCD47EE.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/9E75BBE66CECE729014DFB359A4E6A7413E935B58547C9690620CAF0077D6C52.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/0000000000000000000000000000000000000000000000000000000000000000.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/E29C9C180C6279B0B02ABD6A1801C7C04082CF486EC027AA13515E4F3884BB6B.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/AE21AAF9CA7A3B0EA31C925C294A428E8235DD9F462167BC3694A52E325E7F3B.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/CEAA28BBA4CABA687DC31B1BBE79ECA3C70C33F871F1CE8F528CF9AB5CFD76DD.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/6B86B273FF34FCE19D6B804EFF5A3F5747ADA4EAA22F1D49C01E52DDB7875B4B.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/6.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/02D20BBD7E394AD5999A4CEBABAC9619732C343A4CAC99470C03E23BA2BDC2BC.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/3BB93FB0F0C241E3772322788F65C6688715253F85DF1B7B65EB098D6C4A60BD.jpg",
"/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/minus_eyea.jpg"};

		const char* path="/home/roland/Documents/CLibs/sek_photo/SEK_Photo/tests_data/41d3e943fe9d6bad2aae.jpeg";
        int i=0;
        for (i=0; i<0;i++){
            printf("\n\n\nCHECKING NOW =>%s\n\n", mass[i]);
            lets_check("./ci_configuration.json", mass[i]);
        }

        lets_check("./ci_configuration.json", path);
        return 0;
};



