extern "C"
{
  int
  echo_toolkit_init (int argc, char *argv[]);
}

int
main (int argc, char* argv[])
{
  return echo_toolkit_init (argc, argv);
}
