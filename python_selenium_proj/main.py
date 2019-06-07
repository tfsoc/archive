import time
import argparse
from argparse import RawTextHelpFormatter
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.action_chains import ActionChains

parser = argparse.ArgumentParser(formatter_class=RawTextHelpFormatter)
parser.add_argument("-c", "--with-click", \
                    help="use mouse click instead of keyboard press", \
                    action="store_true", \
                    default = False)
parser.add_argument("-m", "--game-mode", \
                    help="Survival=0,\n Classic=1,\n Combo=2,\n Hattrick=3,\n Random=4", \
                    type=int, \
                    choices = [0,1,2,3,4],
                    default = 2)
args = parser.parse_args()

if args.with_click == False:
    print("Running in default keypress simulation mode")
    def invokeSkill(n):
        n = int(n)
        if n == 0:
            combo = 'qqqr'
        elif n == 1:
            combo = 'qqwr'
        elif n == 2:
            combo = 'qqer'
        elif n == 3:
            combo = 'wwwr'
        elif n == 4:
            combo = 'wwqr'
        elif n == 5:
            combo = 'wwer'
        elif n == 6:
            combo = 'eeer'
        elif n == 7:
            combo = 'eeqr'
        elif n == 8:
            combo = 'eewr'
        elif n == 9:
            combo = 'qwer'
        ActionChains(driver).send_keys(combo).perform()
    def castSkill():
        ActionChains(driver).send_keys('d').perform()
else:
    print("Running in click simulation mode")
    def invokeSkill(n):
        n = int(n)
        q = driver.find_element_by_xpath("//div[@class='hotkey hotkey1']")
        w = driver.find_element_by_xpath("//div[@class='hotkey hotkey2']")
        e = driver.find_element_by_xpath("//div[@class='hotkey hotkey3']")
        r = driver.find_element_by_xpath("//div[@class='hotkey hotkey6']")
        if n == 0:
            [x.click() for x in [q,q,q,r]]
        elif n == 1:
            [x.click() for x in [q,q,w,r]]
        elif n == 2:
            [x.click() for x in [q, q, e,r]]
        elif n == 3:
            [x.click() for x in [w, w, w,r]]
        elif n == 4:
            [x.click() for x in [w, w, q,r]]
        elif n == 5:
            [x.click() for x in [w, w, e,r]]
        elif n == 6:
            [x.click() for x in [e,e,e,r]]
        elif n == 7:
            [x.click() for x in [e, e, q,r]]
        elif n == 8:
            tmp = [x.click() for x in [e, e, w,r]]
        elif n == 9:
            tmp = [x.click() for x in [q, w, e, r]]
    def castSkill():
        driver.find_element_by_xpath("//div[@class='hotkey hotkey4']").click()
        
driver = webdriver.Chrome()
driver.get('https://www.invokergame.com/')

gameMode = driver.find_elements_by_class_name('GameModeButton')[args.game_mode]
gameMode.click()

noLogin = driver.find_element_by_xpath("//a[@href='javascript:void()']")
noLogin.click()

start = driver.find_element_by_class_name('ButtonStart')
start.click()

task = driver.find_element_by_class_name('speechboxHeadline')
while task.text!='':
    spells = driver.find_elements_by_xpath("//tr[@class='speechboxTR']/td")
    castButton = driver.find_element_by_xpath("//div[@class='hotkey hotkey4']")
    if task.text == 'Invoke Spell(s)':
        for spell in spells:
            invokeSkill(spell.get_attribute('id')[6:])
    elif task.text == 'Invoke and Cast':
        for spell in spells:
            invokeSkill(spell.get_attribute('id')[6:])
            castSkill()
    task = driver.find_element_by_class_name('speechboxHeadline')


time.sleep(5)
driver.quit()