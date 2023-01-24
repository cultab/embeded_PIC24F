
def adc_to_celcius(value):
    """
    adc / 4096 = mV / (Vref+ - Vref-)
    mV = (adc / 4096) * (Vref+ - Vref-) (1)
    
    Vout(mV) = 10mV * temp(C) + 500
    temp(C) = (Vout(mV) - 500) / 10 (2)
    
    
    from (1), (2)
    
    temp(C) = {[(adc/4096) * (Vref+ - Vref-)] - 500} / 10
    """
    
    
    Vrefp = 3300.0 # mV
    Vrefn = 0.0    # mV
    adc_stages = 4096.0

    mV = (value * Vrefp - Vrefn)/adc_stages
    print(mV)
    print((mV - 500) / 10)

def mv_to_celcius(mV):
    Vrefp = 3300.0 # mV
    Vrefn = 0.0    # mV
    adc_stages = 4096.0

    temp = (mV - 500) / 10
    print((mV - 500) / 10)
print(adc_to_celcius(950))

def mV_to_adc(mV):
    return (mV / 3300) * 4096
