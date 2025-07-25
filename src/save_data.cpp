#include "save_data.hpp"

void write_grid()
{
    // writing grid.x file
    int nprocs = 1;
    std::string strInf2 = PATH_FILES;
    strInf2 += "/";
    strInf2 += ID_SIM;
    strInf2 += "/";
    strInf2 += "grid.x"; // generate file name (with path)

    std::ofstream gridfile(strInf2, std::ios::binary);
    if (!gridfile)
    {
        std::cerr << "Error opening grid file" << std::endl;
    }
    gridfile.write(reinterpret_cast<const char *>(&nprocs), sizeof(int));
    for (int m = 1; m <= nprocs; ++m)
    {
        gridfile.write(reinterpret_cast<const char *>(&NX), sizeof(int));
        gridfile.write(reinterpret_cast<const char *>(&NY), sizeof(int));
    }

    // Write x and y arrays for each processor (m = 0 to nprocs - 1)
    for (int m = 0; m < nprocs; ++m)
    {
        for (int j = 0; j < NY; ++j)
            for (int i = 0; i < NX; ++i)
            {
                float val = (double(i)) / (NX - 1); // already float
                gridfile.write(reinterpret_cast<const char *>(&val), sizeof(float));
            }

        for (int j = 0; j < NY; ++j)
            for (int i = 0; i < NX; ++i)
            {
                float val = (double(j)) / (NY - 1);
                gridfile.write(reinterpret_cast<const char *>(&val), sizeof(float));
            }
    }
}

void write_solution(dfloat *h_fMom, dfloat *rho, dfloat *ux, dfloat *uy, size_t iter)
{

    // Creating master.p3d file
    std::string strInf = PATH_FILES;
    strInf += "/";
    strInf += ID_SIM;
    strInf += "/";
    strInf += "master.p3d"; // generate file name (with path)
    std::string prefix = "data";
    std::string suffix = ".f";
    std::ostringstream master_file;
    master_file << strInf;
    std::ofstream out(master_file.str());
    out << "{" << std::endl;
    ;
    out << std::endl;
    ;
    out << " \"auto-detect-format\": true," << std::endl;
    ;
    out << std::endl;
    ;
    out << " \"filenames\": [" << std::endl;
    ;
    out << std::endl;
    ;

    for (int iter = 1; iter < MAX_ITER; iter++)
    {
        if (iter % MACR_SAVE == 0)
        {
            std::ostringstream filename_temp;
            filename_temp << prefix << (10000000 + iter) << suffix;
            std::string filename = filename_temp.str();

            if (out.is_open())
            {
                out << "{ \"time\" :  " << iter / MACR_SAVE << ", \"xyz\" : \"grid.x\", \"function\" : \"" << filename << "\" }," << std::endl;
                ;
            }
            else
            {
                std::cerr << "Failed to open file: master.p3d" << std::endl;
            }
        }
    }
    out << std::endl;
    ;
    out << "]" << std::endl;
    ;
    out << "}" << std::endl;
    ;
    out.close();

    // Data file
    for (size_t x = 0; x < NX; x++)
    {
        for (size_t y = 0; y < NY; y++)
        {
            rho[IDX(x, y)] = RHO_0 + h_fMom[MIDX(x, y, M_RHO_INDEX)];
            ux[IDX(x, y)] = h_fMom[MIDX(x, y, M_UX_INDEX)];
            uy[IDX(x, y)] = h_fMom[MIDX(x, y, M_UY_INDEX)];
        }
    }

    // datafile

    std::ostringstream filename_temp;
    int nprocs = 1;
    std::string strInf3 = PATH_FILES;
    strInf3 += "/";
    strInf3 += ID_SIM;
    strInf3 += "/";
    filename_temp << strInf3 << prefix << (10000000 + iter) << suffix;
    std::string filename = filename_temp.str();

    std::ofstream datafile(filename, std::ios::binary);
    if (!datafile)
    {
        std::cerr << "Error opening grid file" << std::endl;
    }

    // Write nprocs
    datafile.write(reinterpret_cast<const char *>(&nprocs), sizeof(int));

    // Write (nx, ny) for each processor (Fortran loop: m = 1 to nprocs)
    for (int l = 0; l < nprocs; ++l)
    {
        datafile.write(reinterpret_cast<const char *>(&NX), sizeof(int));
        datafile.write(reinterpret_cast<const char *>(&NY), sizeof(int));
        int nf = 3; // 3 fields: rho, ux, uy
        datafile.write(reinterpret_cast<const char *>(&nf), sizeof(int));
    }

    // Write x and y arrays for each processor (m = 0 to nprocs - 1)
    for (int m = 0; m < nprocs; ++m)
    {
        // Fortran is column-major: loop j outer, i inner
        for (size_t x = 0; x < NX; x++)
        {
            for (size_t y = 0; y < NY; y++)
            {
                float val = rho[IDX(x, y)]; // already float
                datafile.write(reinterpret_cast<const char *>(&val), sizeof(float));
            }
        }

        for (size_t x = 0; x < NX; x++)
        {
            for (size_t y = 0; y < NY; y++)
            {
                float val = ux[IDX(x, y)];
                datafile.write(reinterpret_cast<const char *>(&val), sizeof(float));
            }
        }

        for (size_t x = 0; x < NX; x++)
        {
            for (size_t y = 0; y < NY; y++)
            {
                float val = uy[IDX(x, y)];
                datafile.write(reinterpret_cast<const char *>(&val), sizeof(float));
            }
        }
        datafile.close();
    }
}