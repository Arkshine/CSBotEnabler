# vim: set sts=2 ts=8 sw=2 tw=99 et:
import sys
from ambuild2 import run

run = run.PrepareBuild(sourcePath = sys.path[0])
run.default_build_folder = 'obj-' + run.target_platform
run.options.add_option('--enable-debug', action='store_const', const='1', dest='debug', help='Enable debugging symbols')
run.options.add_option('--enable-optimize', action='store_const', const='1', dest='opt', help='Enable optimization')
run.options.add_option('--breakpad-dump', action='store_true', dest='breakpad_dump', default=False, help='Dump and upload breakpad symbols')
run.options.add_option('--metamod', type='string', dest='metamod_path', default='../../metamod-am', help='Path to Metamod source code')
run.options.add_option('--hlsdk', type='string', dest='hlsdk_path', default='../../hlsdk', help='Path to the HLSDK')
run.options.add_option('--disable-auto-versioning', action='store_true', dest='disable_auto_versioning', default=False, help='Disable the auto versioning script')
run.Configure()