GDRIVE_PATH='/home/lindsayad/gdrive'

rsync -e "ssh -p 22" -azu --progress --partial lindsayad@152.1.100.198:$GDRIVE_PATH/Presentations/ $GDRIVE_PATH/Presentations/
rsync -e "ssh -p 22" -azu --progress --partial lindsayad@152.1.100.198:$GDRIVE_PATH/Pictures/ $GDRIVE_PATH/Pictures/
rsync -e "ssh -p 22" -azu --progress --partial lindsayad@152.1.100.198:$GDRIVE_PATH/TextDocuments/ $GDRIVE_PATH/TextDocuments/
rsync -e "ssh -p 22" -azu --progress --partial lindsayad@152.1.100.198:$GDRIVE_PATH/Literature/ $GDRIVE_PATH/Literature/
rsync -e "ssh -p 22" -azu --progress --partial lindsayad@152.1.100.198:$GDRIVE_PATH/Personal/ $GDRIVE_PATH/Personal/
rsync -e "ssh -p 22" -azu --progress --partial lindsayad@152.1.100.198:$GDRIVE_PATH/convection_paper/ $GDRIVE_PATH/convection_paper/
rsync -e "ssh -p 22" -azu --progress --partial lindsayad@152.1.100.198:$GDRIVE_PATH/intro_zapdos_paper/ $GDRIVE_PATH/intro_zapdos_paper/
