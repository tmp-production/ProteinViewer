#include "Public/vina.h"
#include "Private/vina.h"

Vina::Vina(const std::string &sf_name, int cpu, int seed, int verbosity, bool no_refine,
           std::function<void(double)> *progress_callback) {
    vina_impl = new IMPL::Vina(sf_name, cpu, seed, verbosity, no_refine, progress_callback);
}

Vina::~Vina() {
    delete ((IMPL::Vina *) vina_impl);
}

void Vina::set_receptor(const std::string &rigid_name, const std::string &flex_name) {
    const auto vina = (IMPL::Vina *) vina_impl;
    vina->set_receptor(rigid_name, flex_name);
}

void Vina::set_ligand_from_string(const std::string &ligand_string) {
    const auto vina = (IMPL::Vina *) vina_impl;
    vina->set_ligand_from_string(ligand_string);
}

void Vina::set_ligand_from_string(const std::vector<std::string> &ligand_string) {
    const auto vina = (IMPL::Vina *) vina_impl;
    vina->set_ligand_from_string(ligand_string);
}

void Vina::set_ligand_from_file(const std::string &ligand_name) {
    const auto vina = (IMPL::Vina *) vina_impl;
    vina->set_ligand_from_file(ligand_name);
}

void Vina::set_ligand_from_file(const std::vector<std::string> &ligand_name) {
    const auto vina = (IMPL::Vina *) vina_impl;
    vina->set_ligand_from_file(ligand_name);
}

void Vina::set_vina_weights(double weight_gauss1, double weight_gauss2, double weight_repulsion,
                            double weight_hydrophobic, double weight_hydrogen, double weight_glue, double weight_rot) {
    const auto vina = (IMPL::Vina *) vina_impl;
    vina->set_vina_weights(weight_gauss1, weight_gauss2, weight_repulsion,
                           weight_hydrophobic, weight_hydrogen, weight_glue, weight_rot);
}

void Vina::set_vinardo_weights(double weight_gauss1, double weight_repulsion, double weight_hydrophobic,
                               double weight_hydrogen, double weight_glue, double weight_rot) {
    const auto vina = (IMPL::Vina *) vina_impl;
    vina->set_vinardo_weights(weight_gauss1, weight_repulsion, weight_hydrophobic,
                              weight_hydrogen, weight_glue, weight_rot);
}

void Vina::set_ad4_weights(double weight_ad4_vdw, double weight_ad4_hb, double weight_ad4_elec,
                           double weight_ad4_dsolv, double weight_glue, double weight_ad4_rot) {
    const auto vina = (IMPL::Vina *) vina_impl;
    vina->set_ad4_weights(weight_ad4_vdw, weight_ad4_hb, weight_ad4_elec,
                          weight_ad4_dsolv, weight_glue, weight_ad4_rot);
}

void Vina::compute_vina_maps(double center_x, double center_y, double center_z,
                             double size_x, double size_y, double size_z,
                             double granularity, bool force_even_voxels) {
    const auto vina = (IMPL::Vina *) vina_impl;
    vina->compute_vina_maps(center_x, center_y, center_z, size_x, size_y, size_z, granularity, force_even_voxels);
}

void Vina::load_maps(const std::string &maps) {
    const auto vina = (IMPL::Vina *) vina_impl;
    vina->load_maps(maps);
}

void Vina::write_maps(const std::string &map_prefix, const std::string &gpf_filename,
                      const std::string &fld_filename, const std::string &receptor_filename) {
    const auto vina = (IMPL::Vina *) vina_impl;
    vina->write_maps(map_prefix, gpf_filename, fld_filename, receptor_filename);
}

void Vina::write_pose(const std::string &output_name, const std::string &remark) {
    const auto vina = (IMPL::Vina *) vina_impl;
    vina->write_pose(output_name, remark);
}

void Vina::write_poses(const std::string &output_name, int how_many, double energy_range) {
    const auto vina = (IMPL::Vina *) vina_impl;
    vina->write_poses(output_name, how_many, energy_range);
}

std::string Vina::get_poses(int how_many, double energy_range) {
    const auto vina = (IMPL::Vina *) vina_impl;
    return vina->get_poses(how_many, energy_range);
}

std::vector<std::vector<double>> Vina::get_poses_coordinates(int how_many, double energy_range) {
    const auto vina = (IMPL::Vina *) vina_impl;
    return vina->get_poses_coordinates(how_many, energy_range);
}

std::vector<std::vector<double>> Vina::get_poses_energies(int how_many, double energy_range) {
    const auto vina = (IMPL::Vina *) vina_impl;
    return vina->get_poses_energies(how_many, energy_range);
}

void Vina::randomize(int max_steps) {
    const auto vina = (IMPL::Vina *) vina_impl;
    vina->randomize(max_steps);
}

std::vector<double> Vina::score() {
    const auto vina = (IMPL::Vina *) vina_impl;
    return vina->score();
}

std::vector<double> Vina::optimize(int max_steps) {
    const auto vina = (IMPL::Vina *) vina_impl;
    return vina->optimize(max_steps);
}

void Vina::global_search(int exhaustiveness, int n_poses, double min_rmsd, int max_evals) {
    const auto vina = (IMPL::Vina *) vina_impl;
    vina->global_search(exhaustiveness, n_poses, min_rmsd, max_evals);
}
