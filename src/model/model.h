#ifndef SRC_MODEL_H_
#define SRC_MODEL_H_

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

namespace s21 {
class Model {
public:
    static Model& Instance() {
        static Model instance;
        return instance;
    }

    std::vector<double>& GetVertex() { return vertex_; }
    std::vector<int>& GetFacets() { return facets_; }
    void SetVertex(std::vector<double>& input) { vertex_.swap(input); }

    void ParseFileData(FILE *fp);
private:
    std::vector<double> vertex_;
    std::vector<int> facets_;

    Model() {}
    ~Model() {}
    Model(const Model&);		// off
    Model& operator=(Model&);	// off

};
}  //  namespace s21

#endif  //  SRC_MODEL_H_
