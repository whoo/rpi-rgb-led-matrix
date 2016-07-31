#include "tools.h"
#define EXIT_WITH_MSG(m) { fprintf(stderr, "%s: %s |%s", (char*)filename.c_str(), m, line); fclose(f); return false; }

Pixel *LoadPPM(std::string filename) {
    Pixel *image_=NULL; 
    int width_,height_;
    FILE *f = fopen((char*)filename.c_str(), "r");
    if (f == NULL) return false;
    char header_buf[256];
    const char *line = ReadLine(f, header_buf, sizeof(header_buf));
    if (sscanf(line, "P6 ") == EOF) EXIT_WITH_MSG("Can only handle P6 as PPM type.");
    line = ReadLine(f, header_buf, sizeof(header_buf));
    if (!line || sscanf(line, "%d %d ", &width_, &height_) != 2) EXIT_WITH_MSG("Width/height expected");
    int value;
    line = ReadLine(f, header_buf, sizeof(header_buf));
    if (!line || sscanf(line, "%d ", &value) != 1 || value != 255) EXIT_WITH_MSG("Only 255 for maxval allowed.");
    const size_t pixel_count = width_ * height_;
    image_ = new Pixel [ pixel_count ];
    //assert(sizeof(Pixel) == 3);   // we make that assumption.
    if (fread(image_, sizeof(Pixel), pixel_count, f) != pixel_count) {
      line = "";
      EXIT_WITH_MSG("Not enough pixels read.");
    }
    fclose(f);
    //horizontal_position_ = 0;
    return image_;
  }
char *ReadLine(FILE *f, char *buffer, size_t len) {
                        char *result;
                        do {
                                result = fgets(buffer, len, f);
                        } while (result != NULL && result[0] == '#');
                        return result;
                }

std::string randomfile() {
        DIR     *Dir=opendir("pixmap");
        struct  dirent *list;
	std::string dd;

        std::vector<std::string> vList;

        while ( list=readdir(Dir) )
        {
		if (list->d_name[0]!='.')
                vList.push_back(list->d_name);
        }

        closedir(Dir);
//        std::cout<<vList.size();
	dd=vList.at(rand()%vList.size());
	//	std::cerr<<dd;
        return "pixmap/"+dd;
}

