cp -R lib logic-component
cp -R lib serial-component

if [ $# -eq 0 ]
  then
    docker compose up -d --build
    exit 0
fi

for service in "$@"
do
    docker compose up -d --build --no-deps $service
done