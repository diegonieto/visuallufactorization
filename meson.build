project(
    'visualLU', 'cpp',
    version: '0.0.1',
)

projectName = 'visualLU'

qt5 = import('qt5')
qt5_dep = dependency(
    'qt5',
    modules: ['Core', 'Gui', 'Widgets']
)

qtprocessed = qt5.preprocess(
    moc_headers: 'lu_main_window.h',
    ui_files: 'lu_main_window.ui'
)

sources = files(
    'main.cpp',
    'lu_main_window.cpp',
)

executable(
    projectName,
    sources,
    qtprocessed,
    dependencies : qt5_dep,
)