import math

def std_ab(list, mean):
    new_list = [] 
    for l in list:
        new_list.append(math.sqrt((l - mean) * (l - mean)))

    return new_list



f = open('Messwerte.txt', 'r' )
print (f)
l = list(f)

temp = []
pressure = []
E_intermol = []
not_in_range = []
for element in l:
    current = element.rsplit()
    if len(current) > 0:
        if 'temperature' in element:
            temp.append(float(current[1]))
        if 'E(intermolecular)' in element:
            E_intermol.append(float(current[1]))
        if 'pressure:' in element:
            pressure.append(float(current[1]))
        if current[0] == 'molecule' and current[1] == '001':
            if current[3] == 'yes':
                not_in_range.append(1)
            else:
                not_in_range.append(0)
        if current[0] == 'molecule' and not current[1] == '001':
            if current[3] == 'yes':
                not_in_range[len(not_in_range) - 1] += 1


mittelwert_temp = sum(temp) / len(temp)
mittelwert_pre = sum(pressure) / len(temp)
mittelwert_e_inter = sum(E_intermol) / len(temp)
mittelwert_nir = sum(not_in_range) / len(temp)

std_t = std_ab(temp, mittelwert_temp)
std_p = std_ab(pressure, mittelwert_pre)
std_E_inter = std_ab(E_intermol, mittelwert_e_inter)
std_nir = std_ab(not_in_range,mittelwert_nir)


print("=== ERGEBNISSE ===")
print()
print("Temperatur:", mittelwert_temp , " +-" ,sum(std_t) / len(temp))
print("Wertebereich:", min(temp), " " , max(temp))
print()
print("Druck:", mittelwert_pre, " +-" ,sum(std_p) / len(temp))
print("Wertebereich:", min(pressure), " " , max(pressure))
print()
print("intermolekulare Energie: ",mittelwert_e_inter, " +-" ,sum(std_E_inter) / len(temp))
print("Wertebereich:", min(E_intermol), " " , max(E_intermol))
print()
print("Molekuele ausser Reichweite: ",mittelwert_nir, " +-" ,sum(std_nir) / len(temp))
print("Wertebereich:", min(not_in_range), " " , max(not_in_range))
print()
print("=== ========== ===")
print()

