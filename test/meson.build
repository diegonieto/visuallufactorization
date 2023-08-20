
gtest_dep = dependency('gtest', main : true, required : true)

test_name = 'TestNumericMatrix'

test = executable(
  test_name,
  sources: ['TestNumericMatrix.cpp'],
  dependencies: gtest_dep,
  include_directories: '..'
)

test('visualmatrixlu-' + test_name, test)
