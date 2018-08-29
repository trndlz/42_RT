# RT

## Eye (Camera Position)
- Object `<eye>`
- Restrictions : Only one eye is defined
- Parameters
    - [position] X Y Z (pixels)
    - [rotation] X Y Z (in degrees)

## Lights Sources
- Object `<light>`
- Parameters:
    - [position] X Y Z (pixels)
    - [rotation] X Y Z (in degrees) -> if not (0,0,0), defines parallel light source
    - [color] 0xABCDEF : Color of specular lighting

## Scene Parameters
- Object `<scene>`
- All global scene parameters are set here
- Parameters
    - +antialias : Sets antialiasing mode on
    - +blinding_lights : Sets blinding lights mode on
    - [filter] : Available filters;
        - RED
        - GREEN
        - BLUE
        - SEPIA
        - STEREOSCOPIC
        - CARTOON
        - CYAN

## Object types
- Available objects `<sphere>` `<plane>` `<cylinder>` `<cone>` `<paraboloid>` `<disc>`
- Parameters:
    - [position] X Y Z (pixels)
	- [rotation] X Y Z (in vector direction)
	- [color] 0xABCDEF (Hexadecimal)
	- [size] in pixels except for `<paraboloid>` and `<cone>` in degrees. For disc, if < 0 : Plane with hole
	- [Spec/Diff/Amb] Phong coefficients (must all be between 0 and 1):
        - Specular
        - Diffuse
        - Ambient
	- [R/T/Rf] Descartes coefficients:
        - Reflection (0 : No reflection at all. 1 : Fully reflective. Must be between 0 and 1)
        - Transparency (0 : Fully opaque. 1 : Fully transparent. Must be between 0 and 1)
        - Refraction (1 : No ray refraction. Must be between 1 and 2)
	- [perturbation] See below
    - [texture] See below
    - `<cutter>` See below

## Perturbations
- Available for all objects with [perturbation] parameter.
- Parameters
    - 0 No perturbation
    - 1 Big squares
    - 2 Large stripes
    - 3 Small squares
    - 4 Grooves

## Textures
- Usage : [texture] TEXTURE_NAME TEXTURE_SIZE (Default size: 0)
- Available textures for `<sphere>`
    - LINES
    - COLUMNS
    - CHECKERBOARD
    - EARTH
    - NEARTH (Bump Mapping)
    - PERLIN (Perlin Noise)
- Available textures for `<plane>`
    - CHECKERBOARD
- Available textures for `<disc>`
    - CHECKERBOARD
- Available textures for `<cylinder>`
    - LINES
- Available textures for `<cone>`
    - LINES

## Cutters
- All objects can be cut. Cutter type is `<plane>` by default.
- By default, Phong and Descartes coefficients are the same as cut object.
- Only non transparent objects are cut (T = 0)
- Parameters:
    - (position) X Y Z (pixels)
	- (rotation) X Y Z (in vector direction)
	
![alt text](https://github.com/trndlz/rtv1/blob/master/img/allobj.png)

![alt text](https://github.com/trndlz/rtv1/blob/master/img/bump.png)

![alt text](https://github.com/trndlz/rtv1/blob/master/img/cut.png)

![alt text](https://github.com/trndlz/rtv1/blob/master/img/sphere.png)
