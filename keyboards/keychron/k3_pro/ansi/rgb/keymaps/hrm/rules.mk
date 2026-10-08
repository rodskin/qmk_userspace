CAPS_WORD_ENABLE = yes
# couche et modificateurs actifs envoyés à l'ordinateur (indicateur Waybar)
RAW_ENABLE = yes
# k3_pro.c définit déjà raw_hid_receive (test usine, DFU Bluetooth) : on la
# renomme raw_hid_receive_k3pro pour ce seul fichier ; raw_hid_receive
# (keymap.c) traite nos messages et lui passe les autres
%/keyboards/keychron/k3_pro/k3_pro.o: INIT_HOOK_CFLAGS += -Draw_hid_receive=raw_hid_receive_k3pro
