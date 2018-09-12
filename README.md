V3DD (vitkit3d_debug_drawings)
==================
A ROCK (http://rock-robotics.org) library that provides methods to create 3d drawings and plot data from inside any code for debugging purpose.

Features
-----------------
* Create and manipulate simple 3D drawings from inside any code
* Create and manipulate 2D plots from inside any code
* Minimal configuration needed
* Drawings can be enabled/disabled using compile switch
* No runtime overhead if disabled
* Three different operation modes:
 * *Standalone mode:* A standalone window pops up automatically to visualize the drawings
 * *Embedded mode:* Drawings can be visualized using an existing Vizkit3DWidget and QApplication context.
 * *Port mode*: Drawings are published using rock ports and can be visualized using rock-display.
* Available 3d primitives include:
 * Box, Arrow, Ring, Sphere, Cylinder, Line, Polyline, Text, AABB, Axes, etc.
 * New primitives can be added by implementing a simple interface (command pattern)



Compiling
-----------------

#### Compiling inside ROCK
Nothing special has to be done to compile inside ROCK. Just call *amake* and wait.

#### Compiling standalone

Several dependencies need to be compiled and installed using a common install prefix.

##### Prepare environment
Create env.sh with following content and source it:
```
export CMAKE_PREFIX_PATH=<PATH_TO_INSTALL_PREFIX>
export PKG_CONFIG_PATH=<PATH_TO_INSTALL_PREFIX>/lib/pkgconfig:<PATH_TO_INSTALL_PREFIX>/share/pkgconfig:<PATH_TO_INSTALL_PREFIX>/lib64/pkgconfig:$PKG_CONFIG_PATH
export LD_LIBRARY_PATH=<PATH_TO_INSTALL_PREFIX>/lib:<PATH_TO_INSTALL_PREFIX>/lib64:$PKG_CONFIG_PATH
export PATH=<PATH_TO_INSTALL_PREFIX>/bin:$PATH
export VIZKIT_PLUGIN_RUBY_PATH=<PATH_TO_INSTALL_PREFIX>/lib
```

Most of the environment variables are only needed while compiling. Only *VIZKIT_PLUGIN_RUBY_PATH* needs to be exported for execution. This variable is used by vizkit3d to locate the visualization plugins.

##### install base-cmake
base-cmake contains special cmake macros that are used in osgviz, vizkit3d and V3DD. 

```
git clone git@github.com:rock-core/base-cmake.git
cd base-cmake
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=<PATH_TO_INSTALL_PREFIX> ..
make -j install
```


##### install osgviz
```
git@github.com:/rock-core/gui-osgviz.git
cd gui-osgviz-osgviz
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=<PATH_TO_INSTALL_PREFIX> ..
make -j install
```
##### install vizkit3d
```
git clone git@github.com:envire/gui-vizkit3d.git
cd gui-vizkit3d
git checkout osgviz
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=<PATH_TO_INSTALL_PREFIX> ..
make -j install
```

##### Build V3DD
Port support needs to be disabled with *WITH_PORTS=OFF* because ports are not availabled without ROCK.
Set *DROCK_TEST_ENABLED=ON* to build the tests.

```
git clone git@github.com:arneboe/gui-vizkit3d_debug_drawings.git
cd gui-vizkit3d_debug_drawings
mkdir build
cmake -DCMAKE_INSTALL_PREFIX=/home/arne/git/debug3d_install -DWITH_PORTS=OFF -DROCK_TEST_ENABLED=ON ..
make -j install
```

Run *draw_test* in *build/test* to check if everything works.


Usage
-----------------

#### Configuration at Compile Time

Every component that contains drawing code needs to link against *libvizkit3d_debug_drawings*.
```
DEPS_PKGCONFIG
    vizkit3d_debug_drawings
```
By default all drawing code is disabled and will be removed by the compiler.
To enable it *ENABLE_DEBUG_DRAWINGS* needs to be defined for every component
containing debug drawing commands.
```
add_definitions(-DENABLE_DEBUG_DRAWINGS)
```
If you do ***not*** use pkg-config and want to use the port features you have to define *USE_PORTS* aswell.
pkg-config knows about this flag and sets it automatically if the library has been built with port support.
```
add_definitions(-DUSE_PORTS)
```


#### Configuration at Runtime
At runtime you need to choose which operation mode should be used to visualize
the drawings. This is done by executing one of the following methods at startup:
```c++
void CONFIGURE_DEBUG_DRAWINGS_STANDALONE();
void CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET(vizkit3d::Vizkit3DWidget* widget);
void CONFIGURE_DEBUG_DRAWINGS_USE_PORT(RTT::TaskContext* taskContext);
```

__Configuration is thread local.__ I.e. one of the configuration methods has to be called
at startup of every new thread if the thread contains drawing code.
An exception will be thrown if any drawing code is executed while V3DD is not
configured.

The configuration cannot be changed. Thus calling `CONFIGURE()` multiple times results in an exception. However sometimes it is convenient from a code perspective (e.g. to avoid the `ìf`) to call 'CONFIGURE()' multiple times. Special `NO_THROW` versions of some configuration methods exists for that case.

```c++
void CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET_NO_THROW(vizkit3d::Vizkit3DWidget* widget);
void CONFIGURE_DEBUG_DRAWINGS_USE_PORT_NO_THROW(RTT::TaskContext* taskContext);
```

At the time of writing the following modes exist:
###### CONFIGURE_DEBUG_DRAWINGS_STANDALONE
In standalone mode a new QThread will be started containing a new QApplication context.
This thread is used to display a Vizkit3DWidget which is used for visualization.

###### CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET
In embedded mode the application expects that there already is a QApplication context
and a Vizkit3DWidget already exists. The existing widget will be used for visualization.

###### CONFIGURE_DEBUG_DRAWINGS_USE_PORT
In port mode the application expects to be running inside a rock task. The context of that task has to be provided. For each drawing a new port will be added to the task and the corresponding drawing commands will be sent through that port. The drawings can be
visualized using rock-display.




#### Simple Drawing
Once configured you can start adding drawing commands anywhere inside your code.
The commands will be executed when the corresponding code path is executed.
Take a look at `vizkit3d_debug_drawings/DebugDrawing.h` for an overview of all available commands.

```c++
#include <vizkit3d_debug_drawings/DebugDrawing.h>
#include <vizkit3d_debug_drawings/DebugDrawingColors.h> //only needed for named colors
```
Example:
```c++
base::Vector3d pos(-3, -3, -3);
DRAW_SPHERE("some_pos", pos, 1, vizkit3dDebugDrawings::Color::red);
```

All drawing commands follow the same structure. The first parameter is always the
name of the drawing group, the last parameter is always the color.
 A list of named colors can be found in `vizkit3d_debug_drawings/DebugDrawingColors.h`. If none of the named colors suits you, you can always define your own. A color is just a `base::Vector4d` containing RGBA values.

The drawing group has special relevance. All drawings that belong to a group
will be visualized by the same instance of a Vizkit3DPlugin or send through the same
port. Thus a user can enable or disable the visualizations on a
per group basis. Groups are __not__ limited to a certain type of drawing. They can contain any mix of drawing types.


#### Complex Drawings
Sometimes a lot of extra instructions (e.g. coordinate transformations) are needed before a drawing command can be issued. While the drawing command itself would be removed when debug drawings are disabled, the extra instructions would remain.
TO avoid this the `COMPLEX_DRAWING` macro can be used. This macro should enclose all code that is only necessary to issue the drawing command. When debug drawings are disabled, the whole macro becomes a noop.

Example:
```c++
COMPLEX_DRAWING(
   base::Vector3d size;
   size.x() = std::abs(areaToExplore.getBox().max().x() - areaToExplore.getBox().min().x());
   size.y() = std::abs(areaToExplore.getBox().max().y() - areaToExplore.getBox().min().y());
   size.z() = std::abs(areaToExplore.getBox().max().z() - areaToExplore.getBox().min().z());
   CLEAR_DRAWING("Exploration_Area");
   DRAW_WIREFRAME_BOX("Exploration_Area", areaToExplore.getCenter(), areaToExplore.getOrientation(), size,vizkit3dDebugDrawings::Color::amber);
);
```

#### Clearing and Removing Drawings
With a lot of drawings the visualization might get
cluttered and laggy. To avoid that the user can clear drawings or remove them altogether. This is done by calling one of the following methods:
```c++
void REMOVE_DRAWING(const std::string& drawingGroupName);
void CLEAR_DRAWING(const std::string& drawingGroupName);
```

`REMOVE_DRAWING` will remove all drawings belonging to the specified group. It will also unload the corresponding Vizkit3DPlugin. Thus `REMOVE_DRAWING` should be called
when you want to permanently remove a group.

`CLEAR_DRAWING` will also remove all drawings belonging to the specified group. But it will not remove the plugin. It should be used when you intended to use the same group name again (e.g. during a later iteration) but want a clean canvas to draw on.


#### Plotting 2D data
In addition to 3D debug drawings, it is also possible to create simple 2D plots.
```
void PLOT_2D(const std::string& plotName, const base::Vector2d& dataPoint);
void CLEAR_PLOT(const std::string& plotName);

```

`PLOT_2D` will add a data point to an existing plot or create a new plot if
the plot doesn't exist. Plots show up as docked widgets in the Vizkit3DWidget.

At the time of writing plots can be cleared but not completely removed. This is likely to change in the future :)

Example:
```c++
double x = 0.0;
while(true)
{
    x += 0.1;
    PLOT_2D("sin", {x,std::sin(x)});
}
```

#### FLUSHING
When sending drawing commands through rock ports the user needs to flush the
send queue regularly. This should be done in the update loop of the corresponding
task.

```c++
void SomeTask::updateHook()
{
    CONFIGURE_DEBUG_DRAWINGS_USE_PORT_NO_THROW(this);
    //your code here
    FLUSH_DRAWINGS();
    }
```


Under the Hood
-----------------

#### Architecture
![Class diagram](https://github.com/arneboe/gui-vizkit3d_debug_drawings/raw/master/doc/class_diagram.png "Class Diagram")


#### Serialization
Commands are serialized using boost to send them through rock ports as opaque type containing a binary blob with the serialized data. The Opaque conversion can be found [in this repository](https://github.com/arneboe/gui-orogen-vizkit3d_debug_drawings).

Boost serialization was chosen over typekit serialization because typekit cannot handle virtual inheritance.


#### Why is the Backend Thread-Local?
As mentioned above the whole backend is thread-local. I.e. a separate instance of the backend exists for each thread. This design was chosen because this library is intended to be used inside the ROCK framework. Most of the time each ROCK task runs in its own thread. Thus to be able to distinguish between drawing commands from different tasks and attach the ports to the correct tasks the library needs to be thread local. Otherwise drawing commands from task *A* might be falsely send to a port on task *B*.

#### Why is the whole drawing state sent through ports every time?
The way rock-display connects ports allows for message loss. I.e. when too may messages are sent, they are dropped. This happens regularly. Thus we have to send the whole drawing state every time. Sending only incremental updates might lead to a corrupt state due to message loss.


Inspiration
-----------------
This project was heavily inspired by the inline drawing macros that can be found
in the [B-Human](https://b-human.de) framework.
See: https://github.com/bhuman/BHumanCodeRelease/blob/master/Src/Tools/Debugging/DebugDrawings3D.h
