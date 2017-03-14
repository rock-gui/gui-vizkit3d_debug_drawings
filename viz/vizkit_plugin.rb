Vizkit::UiLoader.register_3d_plugin('DrawingVisualization', 'vizkit3dDebugDrawings', 'DrawingVisualization')
Vizkit::UiLoader.register_3d_plugin_for('DrawingVisualization', "/vizkti3dDebugDrawings/Drawing", :updateData)

Vizkit::UiLoader.register_3d_plugin('DebugDrawingVisualization', 'vizkit3dDebugCommand', 'DebugDrawingVisualization')
Vizkit::UiLoader.register_3d_plugin_for('DebugDrawingVisualization', "/boost/shared_ptr</vizkit3dDebugDrawings/Command>", :updateData)
