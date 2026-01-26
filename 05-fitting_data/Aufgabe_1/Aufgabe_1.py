import numpy as np

c_messungen = np.array([299793, 299792, 299782])
c_error = np.array([2.0,4.5,25])
 
def mittelwert_gewichtet(n,err):
    return np.sum(n/err**2)/np.sum(1/err**2)
def chi2(c,c_err):
    return np.sum((c-mittelwert_gewichtet(c,c_err))**2/c_err**2)
def innere_varianz(c_err):
    return  1/(np.sum(1 /((c_err)**2)))
def externe_varianz(c,c_err):
    return np.sum((c - mittelwert_gewichtet(c,c_err))**2 / c_err**2)/((np.size(c)-1)*np.sum(1/c_err**2))
# Print results into file
with open(r"./Aufgabe_1/ergebnisse_1.txt", "w") as file:
    file.write(f"gewichteter Mittelwert: {mittelwert_gewichtet(c_messungen,c_error)}\n")
    file.write(f"Chi^2: {chi2(c_messungen,c_error)}\n")
    file.write(f"Interner Fehler: {np.sqrt(innere_varianz(c_error))}\n")
    file.write(f"Externer Fehler: {np.sqrt(externe_varianz(c_messungen,c_error))}\n")
    file.write(f"1/N-M: {(externe_varianz(c_messungen,c_error) / innere_varianz(c_error)) / chi2(c_messungen,c_error)}\n")
    file.close()