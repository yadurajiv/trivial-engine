import time
import trivial

def loaded():
	''' called when script gets loaded '''


def init():
	''' called when script gets initialized '''


def update():
	trivial.currentScene.get("msg").value = "Time: " + time
