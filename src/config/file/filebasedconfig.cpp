#include "filebasedconfig.h"

FileBasedConfig::FileBasedConfig(const char *filename, int x, int y) :
    logic_x(x),
    logic_y(y),
    current_iteration(-1)
{
    ifstream config_stream;
    config_stream.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        config_stream.open(filename);
        int dim;
        config_stream >> dim;
        assert(dim == 2);
        config_stream >> real_y >> real_x >> element_size;
        if(!(config_stream >> iterations_count) || iterations_count == 0)
            iterations_count = -1;
        data = new char[real_x * real_y * element_size];
        config_stream.close();

        setIteration(0);
    } catch(ifstream::failure& e) {
        cerr << "some error :(" << endl;
        throw e;
    }
}

FileBasedConfig::~FileBasedConfig()
{
    if(data) delete[] data;
}

inline int FileBasedConfig::getDimSize(int dim) const
{
    switch(dim) {
    case 0: return real_x;
    case 1: return real_y;
    }
    return 1;
}

int FileBasedConfig::prev()
{
    return setIteration(current_iteration - 1);
}

int FileBasedConfig::next()
{
    return setIteration(current_iteration + 1);
}

int FileBasedConfig::setIteration(int iteration)
{
    if(iteration < 0) return current_iteration_id;
    if(iteration >= iterations_count) return current_iteration_id;

    if(current_iteration != iteration) {
        current_iteration = iteration;

        stringstream filename;
        //filename << "data";
        filename << current_iteration;
        string fn = filename.str();
        while(fn.length() < 4) fn = "0" + fn;
        fn = fn + ".bin";

        ifstream data_stream(fn.c_str(), ifstream::binary);
        if(!data_stream.is_open()) return false;
        size_t size = real_x * real_y * element_size;
        data_stream.read(data, size);
        data_stream.close();
    }

    return iteration;
}
