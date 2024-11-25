#ifndef MAHO_MODEL_C_H
#define MAHO_MODEL_C_H

const unsigned int model_mu_dim1 = 3;

const float model_mu[3] = {
    0.4428571428571432, 1.3809523809523805, 0.09552208071415554
};

const unsigned int model_inv_cov_dim1 = 3;
const unsigned int model_inv_cov_dim2 = 3;

const float model_inv_cov[3][3] = {
    13.22649611012204, 0.542961442195853, -31.60524262848073, 
    0.542961442195853, 2.927698883473752, 0.5588429223950871, 
    -31.60524262848073, 0.5588429223950871, 168.77830677184167
};

#endif //MAHO_MODEL_C_H