from math import sin, cos, pi, sqrt, atan, atan2, exp
import numpy as np
import numpy.random as random

def rand_dist(f, a, b, maxf):
    """
    Returns random numbers between a and b distributed with f
    Warning: this method is very ineffective for strongly varying f

    Advice: Generate the distribution function via random.choice (from numpy)
    Example for GauÃŸ function between -5 and 5, sigma = 1:
    1. Generate the y range: 
    y = np.linspace(-5,5,num=1000)
    2. Generate and normalize the distribution
    py = np.exp(-y*y/2)
    ps = py.sum()
    py = py / ps
    3. Generate 1000 random numbers according to this distribution
    x = random.choice(y,p=py,size=1000)
    """
    while True:
        x, y = random.rand(2)
        x = a + (b-a)*x
        y = y*maxf
        if y <= f(x):
            return x


        
class Electron:

    m = 0.511
    r = 0.0005

    def __init__(self, x, y, z, dphi, dtheta, T):
        """
        Takes the initial position and direction (dphi, dtheta)
        and kinetic energy T in MeV
        """
        self.x = x
        self.y = y
        self.z = z
        self.dphi = dphi
        self.dtheta = dtheta
        self.T = T

    def __repr__(self):
        return str(self.x)+' '+str(self.y)+' '+str(self.z)


    def propagate(self, s):
        """
        Propagates the electron by s in the direction specified
        by dphi, dtheta (this is correct!)
        """
        self.x += s*sin(self.dtheta)*cos(self.dphi)
        self.y += s*sin(self.dtheta)*sin(self.dphi)
        self.z += s*cos(self.dtheta)
        self.T -= 0.1*s/self.T


    def change_direction(self, dphi, dtheta):
        """
        Changes the direction of the electron by dphi and dtheta, 
        with Transformation into local system
        """
        # Get velocity unit vector
        vx = np.sin(self.dtheta) * np.cos(self.dphi)
        vy = np.sin(self.dtheta) * np.sin(self.dphi)
        vz = np.cos(self.dtheta)

        # adjust direction by dphi, dtheta
        vx += np.sin(dtheta) * np.cos(dphi)
        vy += np.sin(dtheta) * np.sin(dphi)
        vz += np.cos(dtheta)

        # normalization
        norm = np.sqrt(vx**2 + vy**2 + vz**2)
        vx /= norm
        vy /= norm
        vz /= norm

        # find new angles
        self.dtheta = np.arccos(vz)
        self.dphi = np.arctan2(vx, vy)

    def scatter(self, other):
        """
        Elastic scattering of electron with other electron,
        the angle by which the electron gets deflected is
        chosen randomly (this is correct!)
        """
        P = sqrt((self.T + self.m)**2 - self.m**2)
        phi = random.uniform(-pi, pi)

        if random.randint(1,10) <= 5: #
            # Moeller scattering (warning: formulas are not correct)
            moeller = lambda x: self.r**2/4*(self.m/P)**2 * (3 + np.cos(x))**2 / (np.sin(x)**4)
            theta_cms = rand_dist(moeller, 0.2, pi/2, moeller(0.2))
            gamma = (self.T + other.m) / np.sqrt(self.m**2 + other.m**2 + 2*self.T*other.m)

            # get new directions (Warning: partially wrong!)
            theta1 = np.sin(theta_cms)/(gamma * (1+np.cos(theta_cms)))	
            theta2 = np.sin(theta_cms)/(gamma * (1-np.cos(theta_cms)))	
            self.change_direction(phi, theta1)
            other.change_direction(-phi, theta2)

            # new momenta and energies 
            P1 = (2*self.m*(self.T + self.m) * P * np.cos(theta1)) / ((self.T + self.m)**2 - P**2 * np.cos(theta1)**2)
            P2 = (2*self.m*(self.T + self.m) * P * np.cos(theta2)) / ((self.T + self.m)**2 - P**2 * np.cos(theta2)**2)
            T1 = np.sqrt((P1**2 + self.m**2)) - self.m
            T2 = np.sqrt((P2**2 + self.m**2)) - self.m

            self.T = T1
            other.T = T2
        
        else:
            # Mott scattering 
            gamma = 1
            beta = np.sqrt(1 - (1 / gamma**2))
            
            mott = lambda x: 1/(self.T**2 * np.sin(x/2)**4) * (1 - beta**2 * np.sin(x/2)**2)
            theta_cms = rand_dist(mott, 0.2, pi/2, mott(0.2))
            
            # get new directions
            theta1 = np.sin(theta_cms)/(gamma * (1+np.cos(theta_cms)))	
            #theta2 = np.sin(theta_cms)/(gamma * (1-np.cos(theta_cms)))	
            self.change_direction(phi, theta1)
            #other.change_direction(-phi, theta2)

            # new momenta and energies 
            P1 = (2*self.m*(self.T + self.m) * P * np.cos(theta1)) / ((self.T + self.m)**2 - P**2 * np.cos(theta1)**2)
            T1 = np.sqrt((P1**2 + self.m**2)) - self.m
            self.T = T1
