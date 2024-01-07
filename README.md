# Fast-Fourier-Transform-Simulation-qt
A beta version of a simple tool for analysing the Fourier transform obtained using the FFT algorithm.

# Screenshot
![image](https://github.com/lukasz-kkk/Fast-Fourier-Transform-Simulation-qt/assets/84326531/cbde3047-2377-4adb-abfd-2c7f81a77e12)

# Usage
Use the "frequency" and "amplitude" sliders to adjust the properties of the generated signal. The combine button is used to combine the generated signal with other signals. The second graph shows the resulting signal.
The resulting FFT functions are created automatically in real time.

The signals are generated using a formula:
$$A * sin(Ft2\pi)+A$$
where
$$A=Amplitude$$
$$F=Frequency$$
$$t=time$$

All added signals appear in the history, in the "Signals history" window.

# Definition
Let 
$$x_0, ... ,x_{n-1}$$  
be complex numbers. The DFT is defined by the formula
$$X_𝜉 = \sum_{t=0}^{T-1}f(t)e^{-2\pi it𝜉}$$
where 
$$e^{i2\pi /n}$$  
is a primitive n'th root of 1.

# Information
Qt 6.6.0 used.

