# SURVIVAL KIT

## About

The Survival Kit is a collection of tools built to aid in designing websites in the browser and in rapid prototyping.

Link: [Survival Kit](http://thecodingdesigner.com/survivalkit)

### Drupal version
It includes many javascript libraries. They're not installed. Rather they're in an directory and ready for you to use if you need them. It also includes a robust framework of Sass files for creating your theme's CSS.

## Requirements

Survival Kit is a Drupal theme, but the real magic comes from the companion Compass extension. See these links for more information and for help in installing the dependencies.

* [Sass](http://sass-lang.com/) `gem install sass --pre`
* [Compass](http://compass-style.org/) `gem install compass`
* [Survival Kit (ruby gem)](https://github.com/canarymason/Survival-Kit) `gem install survivalkit`


## Installation

### The Drupal Stuff
1. Install the Survival Kit theme in the normal way
2. Create a subtheme by copying survivalkit/STARTERKIT to your themes directory. Rename "STARTERKIT" as something unique for your project, like "pocketknife".
3. In your subtheme, rename starterkit.info.txt, so that "starterkit" is the name of your theme and the extention is just .info. Like: pocketknife.info
4. Edit your .info file with the new name for your theme and any other custom values. Be sure to keep the 'base theme  = survivalkit' line.

### The Sass Stuff
1. Open your command line and navigate to the root of your subtheme.
2. Run this command: `compass install survivalkit/drupal`
  * This command copies the javascript and sass files from the Compass extension into your subtheme.

## Use

(assuming a working knowledge of Sass and Compass)

### Sass

/sass/style.sass - Use this file to import other partials
/sass/partials/ - freely edit these partials to establish the basic styles for your site. There are partials here for variables, extends, grids, and a lot more
/sass/your-design-here/ This is where you can add custon and unique style for your site. Go crazy.

### Javascript

TODO: refine the javascript imports and document
