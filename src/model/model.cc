#include "model.h"

namespace s21 {
void Model::ParseFileData(FILE *fp) {
    char str[1024];
    vertex_.clear();
    facets_.clear();
    while (fgets(str, 1024, fp)) {
        if (str[0] == 'v') {
            for (int i = 2; i < (int)strlen(str); i++) {
                if (isdigit(str[i])) {
                    if (str[i - 1] == '-') {
                        vertex_.push_back(atof(&str[i]) * (-1));
                    } else {
                        vertex_.push_back(atof(&str[i]));
                    }
                    while (str[i] != ' ') i++;
                }
            }
        } else if (str[0] == 'f') {
            for (int i = 2; i < (int)strlen(str); i++) {
                if (isdigit(str[i])) {
                    facets_.push_back(atof(&str[i]) - 1);
                    while (str[i] != ' ') i++;
                    if (facets_.size() % 2 == 0) {
                        facets_.push_back(facets_[facets_.size() - 1]);
                    }
                }
            }
            int t = atof(&str[2]) - 1;
            facets_[facets_.size() - 1] = t;
            facets_.push_back(facets_[facets_.size() - 2]);
        }
    }
}
}
