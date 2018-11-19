import random
import numpy
import matplotlib.pyplot

data = [6176, 11046, 670, 6146, 7945, 6864, 767, 7623, 7212, 9040, 3213, 6302, 10044, 10195, 9386, 7230, 4602, 6282, 8619, 7903, 6318, 13294, 6990, 5515, 9157]

# Fit gamma distribution through mean and average
mean_of_distribution = numpy.mean(data)
variance_of_distribution = numpy.var(data)

def gamma_random_sample(mean, variance, size):
    """Yields a list of random numbers following a gamma distribution defined by mean and variance"""
    g_alpha = mean*mean/variance
    g_beta = mean/variance
    for i in range(size):
        yield random.gammavariate(g_alpha,1/g_beta)

# force integer values to get integer sample
grs = [int(i) for i in gamma_random_sample(mean_of_distribution,variance_of_distribution,len(data))]

print("Original data: ", sorted(data))
print("Random sample: ", sorted(grs))

plot(grs)