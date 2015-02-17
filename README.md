# eos-ttl-flash-manual-power-controller
Software and Hardware to control the power of old Canon EOS TTL flash/speedlite.

##Rationale

Digital EOS cameras uses E-TTL/E-TTLII flash system wich requires compatible E-TTL/E-TTLII flashes also known as speedlites in Canon world.

Film EOS cameras uses older TTL/A-TTL flash system with requires TTL/A-TTL compatible speedlites.

Newer E-TTL speedlites, with model ending in "EX", are backwards compatible - with a few exceptions - with A-TTL film cameras. Older A-TTL speedlites are only usable in digital EOS in manual power, with no automated TTL metering/exposure.

Few film-era speedlites does not have dedicated user interface to control flash power, as is the case of Canon Macrolite ML- 3, firing always in full power and rendering the unit pratically useless in real situations without troublesome workarounds such as the use of ND filters on flash head.

This project aims to build a small and simple power controller for EOS TTL speedlites.

##The Concept

Canon A-TTL/E-TTL/E-TTLII speedlites have a hotshoe pin called "quench" which enables the flash light to be shutdown before the end of the full power flash, providing a way to control the amount of flash power iluminating the scene.

The general idea of this project is to control the quench time to generate the right amount of flash duration corresponding to a user selectable power.

Long story short, we need to detect the flash trigger signal (comming from the camera) and react (almost) instantly by controlling the quench pin as a real EOS film camera would do in TTL mode.
