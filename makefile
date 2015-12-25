# BREWING THE INTERNET
src=brew.ino
out=output.bin
sid=mrcoffi

# use `make getid` to set sparkid externally
# export sparkid=$(make getid)

all: clean compile
	@echo Target Particle = $(sid)
	particle flash $(sid) $(out)

clean:
	find . -type f -iname "core_firmware_*" -exec rm {} \;

compile: *.ino
	particle compile core $(src)
	mv core_firmware_* $(out)

