*** Settings ***
Library           cnx.py
Variables         hostname.py

*** Test Cases ***
reboot
    cnx.raz    ${ip}    ${registre}    ${valeur1}
    cnx.raz    ${ip}    ${registre}    ${valeur2}
