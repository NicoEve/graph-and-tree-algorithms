from pypresence import Presence
import time

CLIENT_ID = "1345937604595683348"  # Debes crear una app en https://discord.com/developers/applications
rpc = Presence(CLIENT_ID)
rpc.connect()

rpc.update(state="Editing zlatan.cpp", details="Workspace: Ejercicio Parcial", large_image="clion")

while True:
    time.sleep(15)  # Actualiza cada 15 segundos
