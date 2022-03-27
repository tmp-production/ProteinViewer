#pragma once

#include <stdlib.h>
#include <string>
#include <vector>

#ifdef VINA_API
#undef VINA_API
#define VINA_API __attribute__((visibility("default")))
#endif

// TODO: Add documentation to the Vina instance methods
// https://github.com/ccsb-scripps/AutoDock-Vina/blob/develop/build/python/vina/vina.py

class VINA_API Vina {
public:
    Vina(const std::string &sf_name="vina", int cpu=0, int seed=0, int verbosity=1, bool no_refine=false, std::function<void(double)>* progress_callback = NULL);
    ~Vina();
    
    void cite();
    int seed();
    
    void set_receptor(const std::string &rigid_name=std::string(), const std::string &flex_name=std::string());
    void set_ligand_from_string(const std::string &ligand_string);
    void set_ligand_from_string(const std::vector<std::string> &ligand_string);
    void set_ligand_from_file(const std::string& ligand_name);
    void set_ligand_from_file(const std::vector<std::string>& ligand_name);
	void set_vina_weights(double weight_gauss1=-0.035579, double weight_gauss2=-0.005156,
						       double weight_repulsion=0.840245, double weight_hydrophobic=-0.035069,
						       double weight_hydrogen=-0.587439, double weight_glue=50,
						       double weight_rot=0.05846);
	void set_vinardo_weights(double weight_gauss1=-0.045,
							       double weight_repulsion=0.8, double weight_hydrophobic=-0.035,
							       double weight_hydrogen=-0.600, double weight_glue=50,
							       double weight_rot=0.05846);
	void set_ad4_weights(double weight_ad4_vdw=0.1662, double weight_ad4_hb=0.1209,
						      double weight_ad4_elec=0.1406, double weight_ad4_dsolv=0.1322,
						      double weight_glue=50, double weight_ad4_rot=0.2983);
	void compute_vina_maps(double center_x, double center_y, double center_z,
								  double size_x, double size_y, double size_z,
								  double granularity=0.5, bool force_even_voxels=false);
	void load_maps(std::string maps);
	void randomize(const int max_steps=10000);
    std::vector<double> score();
    std::vector<double> optimize(const int max_steps=0);
    void global_search(const int exhaustiveness=8, const int n_poses=20, const double min_rmsd=1.0, const int max_evals=0);
    std::string get_poses(int how_many=9, double energy_range=3.0);
    std::vector< std::vector<double> > get_poses_coordinates(int how_many=9, double energy_range=3.0);
    std::vector< std::vector<double> > get_poses_energies(int how_many=9, double energy_range=3.0);
    void write_pose(const std::string &output_name, const std::string &remark = std::string());
    void write_poses(const std::string &output_name, int how_many=9, double energy_range=3.0);
    void write_maps(const std::string& map_prefix="receptor", const std::string& gpf_filename="NULL",
                        const std::string& fld_filename="NULL", const std::string& receptor_filename="NULL");
    void show_score(const std::vector<double> energies);

private:
    void *vina_impl;
};