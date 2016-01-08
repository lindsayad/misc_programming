GDRIVE_PATH='/home/lindsayad/gdrive'

rsync -e "ssh -p 22" -azu --progress --partial $GDRIVE_PATH/Presentations/ lindsayad@152.1.100.198:$GDRIVE_PATH/Presentations
rsync -e "ssh -p 22" -azu --progress --partial $GDRIVE_PATH/Pictures/ lindsayad@152.1.100.198:$GDRIVE_PATH/Pictures
rsync -e "ssh -p 22" -azu --progress --partial $GDRIVE_PATH/TextDocuments/ lindsayad@152.1.100.198:$GDRIVE_PATH/TextDocuments
rsync -e "ssh -p 22" -azu --progress --partial $GDRIVE_PATH/Literature/ lindsayad@152.1.100.198:$GDRIVE_PATH/Literature
rsync -e "ssh -p 22" -azu --progress --partial $GDRIVE_PATH/Personal/ lindsayad@152.1.100.198:$GDRIVE_PATH/Personal
