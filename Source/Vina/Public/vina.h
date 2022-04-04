#pragma once

#include <cstdlib>
#include <string>
#include <vector>

#ifdef VINA_API
#undef VINA_API
#endif

#define VINA_API __attribute__((visibility("default")))

class VINA_API Vina {
public:
    /// Initialize a Vina object.
    /// \param sf_name Scoring function name to use (Vina or ad4) (default: vina)
    /// \param cpu Number of CPU to use (default: 0; use all of them)
    /// \param seed Random seed (default: 0; randomly chosen)
    /// \param verbosity verbosity 0: not output, 1: normal, 2: verbose (default: 1; some output)
    /// \param no_refine when receptor is provided, do not use explicit receptor atoms
    /// (instead of precalculated grids) for: (1) local optimization and scoring after docking,
    /// (2) --local_only jobs, and (3) --score_only jobs (default: False)
    explicit Vina(const std::string &sf_name = "vina", int cpu = 0, int seed = 0, int verbosity = 1,
                  bool no_refine = false, std::function<void(double)> *progress_callback = nullptr);

    /// Deinitialize a Vina object.
    ~Vina();

    /// Set receptor.
    /// \param rigid_name rigid pdbqt receptor filename
    /// \param flex_name flexible residues pdbqt filename
    void set_receptor(const std::string &rigid_name = std::string(), const std::string &flex_name = std::string());

    /// Set ligand from a string. The chemical file format must be PDBQT.
    /// \param ligand_string PDBQT string
    void set_ligand_from_string(const std::string &ligand_string);

    /// Set ligands from a string. The chemical file format must be PDBQT.
    /// \param ligand_string vector of PDBQT strings
    void set_ligand_from_string(const std::vector<std::string> &ligand_string);

    /// Set ligand from a file. The chemical file format must be PDBQT.
    /// \param ligand_name PDBQT filename
    void set_ligand_from_file(const std::string &ligand_name);

    /// Set ligands from a file. The chemical file format must be PDBQT.
    /// \param ligand_name vector of PDBQT filenames
    void set_ligand_from_file(const std::vector<std::string> &ligand_name);

    /// Set potential weights for vina scoring function.
    void set_vina_weights(double weight_gauss1 = -0.035579, double weight_gauss2 = -0.005156,
                          double weight_repulsion = 0.840245, double weight_hydrophobic = -0.035069,
                          double weight_hydrogen = -0.587439, double weight_glue = 50,
                          double weight_rot = 0.05846);

    /// Set potential weights for vinardo scoring function.
    void set_vinardo_weights(double weight_gauss1 = -0.045,
                             double weight_repulsion = 0.8, double weight_hydrophobic = -0.035,
                             double weight_hydrogen = -0.600, double weight_glue = 50,
                             double weight_rot = 0.05846);

    /// Set potential weights for ad4 scoring function.
    void set_ad4_weights(double weight_ad4_vdw = 0.1662, double weight_ad4_hb = 0.1209,
                         double weight_ad4_elec = 0.1406, double weight_ad4_dsolv = 0.1322,
                         double weight_glue = 50, double weight_ad4_rot = 0.2983);

    /// Compute affinity maps using Vina scoring function.
    /// \param center_x center position (X)
    /// \param center_y center position (Y)
    /// \param center_z center position (Z)
    /// \param size_x size of the box in Angstrom (X)
    /// \param size_y size of the box in Angstrom (Y)
    /// \param size_z size of the box in Angstrom (Z)
    /// \param granularity grid spacing (default: 0.5)
    /// \param force_even_voxels Force the number of voxels (NPTS/NELEMENTS) to be an even number
    /// (and forcing the number of grid points to be odd) (default: false)
    void compute_vina_maps(double center_x, double center_y, double center_z,
                           double size_x, double size_y, double size_z,
                           double granularity = 0.5, bool force_even_voxels = false);

    /// Load vina or ad4 affinity maps.
    /// \param maps affinity map prefix filename
    void load_maps(const std::string &maps);

    /// Write affinity maps.
    /// \param map_prefix affinity map pathname (path directory + prefix)
    /// \param gpf_filename grid protein filename (default: NULL)
    /// \param fld_filename fld filename (default: NULL)
    /// \param receptor_filename receptor filename (default: NULL)
    void write_maps(const std::string &map_prefix = "receptor", const std::string &gpf_filename = "NULL",
                    const std::string &fld_filename = "NULL", const std::string &receptor_filename = "NULL");

    /// Write pose (after randomize or optimize).
    /// \param output_name output PDBQT filename
    /// \param remark REMARKS to add in the PDBQT filename
    void write_pose(const std::string &output_name, const std::string &remark = std::string());

    /// Write poses from docking.
    /// \param output_name PDBQT file containing poses found
    /// \param how_many number of poses to write (default: 9)
    /// \param energy_range maximum energy difference from best pose (default: 3.0 kcal/mol)
    void write_poses(const std::string &output_name, int how_many = 9, double energy_range = 3.0);

    /// Get poses from docking.
    /// \param how_many number of poses to retrieve (default: 9)
    /// \param energy_range maximum energy difference from best pose (default: 3.0 kcal/mol)
    /// \return PDBQT file strings
    std::string get_poses(int how_many = 9, double energy_range = 3.0);

    /// Get poses from docking.
    /// \param how_many number of poses to retrieve (default: 9)
    /// \param energy_range maximum energy difference from best pose (default: 3.0 kcal/mol)
    /// \return vector of coordinates of poses
    std::vector<std::vector<double>> get_poses_coordinates(int how_many = 9, double energy_range = 3.0);

    /// Get pose energies from docking.
    /// \param how_many number of poses to retrieve (default: 9)
    /// \param energy_range maximum energy difference from best pose (default: 3.0 kcal/mol)
    /// \return vector of energies from each pose (rows=poses, columns=energies)\n
    /// Vina/Vinardo FF: columns=[total, inter, intra, torsions, intra best pose]\n
    /// AutoDock FF: columns=[total, inter, intra, torsions, -intra]
    std::vector<std::vector<double>> get_poses_energies(int how_many = 9, double energy_range = 3.0);

    /// Randomize the input ligand conformation.
    void randomize(int max_steps = 10000);

    /// Score current pose.
    /// \return vector of energies from current pose.\n
    /// Vina/Vinardo FF: columns=[total, lig_inter, flex_inter, other_inter, flex_intra, lig_intra, torsions, lig_intra best pose]\n
    /// AutoDock FF: columns=[total, lig_inter, flex_inter, other_inter, flex_intra, lig_intra, torsions, -lig_intra]
    std::vector<double> score();

    /// Quick local BFGS energy optimization.
    /// \param max_steps Maximum number of local minimization steps (default: 0). When max_steps is equal to 0,
    /// the maximum number of steps will be equal to (25 + num_movable_atoms) / 3).
    /// \return Array of energies from optimized pose.\n
    /// Vina/Vinardo FF: columns=[total, lig_inter, flex_inter, other_inter, flex_intra, lig_intra, torsions, lig_intra best pose]\n
    /// AutoDock FF: columns=[total, lig_inter, flex_inter, other_inter, flex_intra, lig_intra, torsions, -lig_intra]
    std::vector<double> optimize(int max_steps = 0);

    /// Docking: global search optimization.
    /// \param exhaustiveness Number of MC run (default: 8)
    /// \param n_poses number of pose to generate (default: 20)
    /// \param min_rmsd minimum RMSD difference between poses (default: 1.0 Ansgtrom)
    /// \param max_evals Maximum number of evaluation (default: 0; use heuristics rules)
    void global_search(int exhaustiveness = 8, int n_poses = 20, double min_rmsd = 1.0, int max_evals = 0);

private:
    void *vina_impl;
};