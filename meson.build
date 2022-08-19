project('opengl-lightning', 'c', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])

inc = include_directories('include')
subdir('src')

compiler = meson.get_compiler('cpp')

deps = [
  dependency('gl'),
  dependency('glfw3'),
  dependency('glew'),
  dependency('glm'),
  dependency('fmt', version: '>=9.0.0')
  ]

exe = executable('opengl_lightning', sources,
  install : true,
  include_directories: inc,
  dependencies: deps)

test('basic', exe)
